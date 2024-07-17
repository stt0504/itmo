import datetime
import os

import psycopg2
from psycopg2 import sql

DB_NAME = os.getenv('POSTGRES_DB')
DB_USER = os.getenv('POSTGRES_USER')
DB_PASSWORD = os.getenv('POSTGRES_PASSWORD')
DB_HOST = os.getenv('POSTGRES_HOST')
DB_PORT = os.getenv('POSTGRES_PORT')
QUERY_ATTEMPTS = int(os.getenv('QUERY_ATTEMPTS'))
day = os.getenv('DAY')
visitor_id = os.getenv('VISITOR_ID')

def execute_explain_analyze(query, params=None):

    conn = psycopg2.connect(
        dbname=DB_NAME, user=DB_USER, password=DB_PASSWORD, host=DB_HOST, port=DB_PORT
    )
    cursor = conn.cursor()
    if params is None:
        cursor.execute(f"EXPLAIN ANALYZE {query}")
    else:
        cursor.execute(f"EXPLAIN ANALYZE {query}", params)
    results = cursor.fetchall()
    cursor.close()
    conn.close()
    return results

def parse_cost(results):
    for row in results:
        if "cost=" in row[0]:
            parts = row[0].split("cost=")[1].split("..")
            startup_cost = float(parts[0])
            total_cost = float(parts[1].split()[0])
            return startup_cost, total_cost
    return None, None

def run_queries(queries):
    all_results = {}
    for query in queries:
        costs = []
        for _ in range(QUERY_ATTEMPTS):
            results = execute_explain_analyze(query['query'], query.get('params'))
            startup_cost, total_cost = parse_cost(results)
            if total_cost is not None:
                costs.append(total_cost)

        if costs:
            all_results[query['query']] = {
                'best': min(costs),
                'average': sum(costs) / len(costs),
                'worst': max(costs)
            }
    return all_results


def save_results(results):
    timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
    filename = f"results/query_performance_{timestamp}.txt"

    with open(filename, 'w') as f:
        for query, metrics in results.items():
            f.write(f"Query: {query}\n")
            f.write(f"Best Case: {metrics['best']}\n")
            f.write(f"Average Case: {metrics['average']}\n")
            f.write(f"Worst Case: {metrics['worst']}\n")
            f.write("\n")

if __name__ == "__main__":
    queries = [
        {
            'query': '''SELECT Instructor_ID, Name, Surname
                        FROM Instructor
                        WHERE Instructor_ID NOT IN (SELECT Instructor_ID
                                       FROM Instructor_Schedule
                                       WHERE Day = %s);''',
            'params': (day,)
        },
        {
            'query': '''SELECT
                            Instructor.Instructor_ID,
                            Instructor.Name,
                            Instructor.Surname,
                            COUNT(Lesson_Appointment.Appointment_ID) AS lesson_count
                         FROM
                            Instructor
                         LEFT JOIN
                            Lesson_Appointment ON Instructor.Instructor_ID = Lesson_Appointment.Instructor_ID
                         GROUP BY
                            Instructor.Instructor_ID, Instructor.Name, Instructor.Surname;'''
        },
        {
            'query': '''SELECT
                            Ticket_ID,
                            Start_date,
                            Finish_date
                         FROM
                            Ticket_partition
                         WHERE
                            Visitor_ID = %s
                            AND Finish_date > CURRENT_DATE;''',
            'params': (visitor_id,)
        },
        {
            'query': '''SELECT EXTRACT(DOW FROM Appointment.Start_time) AS day_of_week,
                               AVG(Visitor.Visitor_ID) AS average_visitors
                        FROM Appointment
                                 JOIN
                             Ticket ON Appointment.Ticket_ID = Ticket.Ticket_ID
                                 JOIN
                             Visitor ON Ticket.Visitor_ID = Visitor.Visitor_ID
                        WHERE Appointment.Start_time >= CURRENT_DATE - INTERVAL '2 years'
                        GROUP BY day_of_week;'''
        }
    ]
    results = run_queries(queries)
    save_results(results)
