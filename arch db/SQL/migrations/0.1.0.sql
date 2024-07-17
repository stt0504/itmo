CREATE TABLE IF NOT EXISTS Visitor
(
    Visitor_ID    SERIAL PRIMARY KEY,
    Name          VARCHAR(20),
    Surname       VARCHAR(20),
    Date_of_birth DATE,
    Phone_number  VARCHAR(20),
    Email         VARCHAR(50)
);

CREATE TABLE IF NOT EXISTS Locker
(
    Locker_ID      SERIAL PRIMARY KEY,
    Visitor_ID     INTEGER,
    Section_number INTEGER,
    FOREIGN KEY (Visitor_ID) REFERENCES Visitor (Visitor_ID)
);

CREATE TABLE IF NOT EXISTS Comment
(
    Comment_ID   SERIAL PRIMARY KEY,
    Visitor_ID   INTEGER,
    Visit_date   TIMESTAMP,
    Comment_date TIMESTAMP,
    Rating       SMALLINT,
    Description  VARCHAR(1000),
    FOREIGN KEY (Visitor_ID) REFERENCES Visitor (Visitor_ID)
);

CREATE TABLE IF NOT EXISTS Equipment
(
    Equipment_ID SERIAL PRIMARY KEY,
    Type         VARCHAR(255),
    Visitor_ID   INTEGER,
    FOREIGN KEY (Visitor_ID) REFERENCES Visitor (Visitor_ID)
);

CREATE TABLE IF NOT EXISTS Rent_of_equipment (
    Rent_ID SERIAL PRIMARY KEY,
    Visitor_ID INTEGER,
    Equipment_ID INTEGER,
    Start_time TIMESTAMP,
    End_time TIMESTAMP,
    FOREIGN KEY (Visitor_ID) REFERENCES Visitor(Visitor_ID),
    FOREIGN KEY (Equipment_ID) REFERENCES Equipment(Equipment_ID)
);

CREATE TABLE IF NOT EXISTS Instructor (
    Instructor_ID SERIAL PRIMARY KEY,
    Name VARCHAR(20),
    Surname VARCHAR(20),
    Cost_for_hour_lesson INTEGER
);

CREATE TABLE IF NOT EXISTS Instructor_schedule (
    Instructor_ID INTEGER,
    Day DATE,
    Start_time TIME,
    End_time TIME,
    PRIMARY KEY (Instructor_ID, Day),
    FOREIGN KEY (Instructor_ID) REFERENCES Instructor(Instructor_ID)
);

CREATE TABLE IF NOT EXISTS Ticket (
    Ticket_ID SERIAL PRIMARY KEY,
    Start_date TIMESTAMP,
    Finish_date TIMESTAMP,
    Visitor_ID INTEGER,
    FOREIGN KEY (Visitor_ID) REFERENCES Visitor(Visitor_ID)
);

CREATE TABLE IF NOT EXISTS Lesson_appointment (
    Appointment_ID SERIAL PRIMARY KEY,
    Visitor_ID INTEGER,
    Instructor_ID INTEGER,
    Start_time TIMESTAMP,
    End_time TIMESTAMP,
    FOREIGN KEY (Visitor_ID) REFERENCES Visitor(Visitor_ID),
    FOREIGN KEY (Instructor_ID) REFERENCES Instructor(Instructor_ID)
);

CREATE TABLE IF NOT EXISTS Attraction (
    Attraction_ID SERIAL PRIMARY KEY,
    Name VARCHAR(20),
    Required_age SMALLINT,
    Description VARCHAR(255)
);

CREATE TABLE IF NOT EXISTS Appointment (
    Appointment_ID SERIAL PRIMARY KEY,
    Ticket_ID INTEGER,
    Attraction_ID INTEGER,
    Start_time TIMESTAMP,
    End_time TIMESTAMP,
    FOREIGN KEY (Ticket_ID) REFERENCES Ticket(Ticket_ID),
    FOREIGN KEY (Attraction_ID) REFERENCES Attraction(Attraction_ID)
);

CREATE TABLE IF NOT EXISTS Visit_number (
    Ticket_ID INTEGER,
    Attraction_ID INTEGER,
    Number INTEGER,
    PRIMARY KEY (Ticket_ID, Attraction_ID),
    FOREIGN KEY (Ticket_ID) REFERENCES Ticket(Ticket_ID),
    FOREIGN KEY (Attraction_ID) REFERENCES Attraction(Attraction_ID)
);

CREATE TABLE IF NOT EXISTS Attraction_schedule (
    Attraction_ID INTEGER,
    Day DATE,
    Start_time TIME,
    End_time TIME,
    PRIMARY KEY (Attraction_ID, Day),
    FOREIGN KEY (Attraction_ID) REFERENCES Attraction(Attraction_ID)
);