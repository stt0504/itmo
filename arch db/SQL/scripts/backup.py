import datetime
import os
import time
from datetime import datetime
import subprocess

DB_NAME = os.getenv('POSTGRES_DB')
DB_USER = os.getenv('POSTGRES_USER')
DB_PASSWORD = os.getenv('POSTGRES_PASSWORD')
DB_HOST = os.getenv('POSTGRES_HOST')
DB_PORT = os.getenv('POSTGRES_PORT')
BACKUP_DIR = os.getenv('BACKUP_DIR')
INTERVAL_HOURS = int(os.getenv('INTERVAL_HOURS'))
NUM_TO_KEEP = int(os.getenv('NUM_TO_KEEP'))

def create_backup(database_name, backup_dir):
    timestamp = datetime.now().strftime('%Y%m%d%H%M%S')
    backup_file = os.path.join(backup_dir, f'{database_name}_backup_{timestamp}.sql')
    command = (
        f'PGPASSWORD={DB_PASSWORD} pg_dump -h {DB_HOST} -p {DB_PORT} '
        f'-U {DB_USER} -d {DB_NAME} > {backup_file}'
    )
    subprocess.run(command, shell=True)

def cleanup_backups(backup_dir, num_to_keep):
    backup_files = sorted(os.listdir(backup_dir), key=lambda x: os.path.getctime(os.path.join(backup_dir, x)), reverse=True)
    files_to_delete = backup_files[num_to_keep:]
    for file_to_delete in files_to_delete:
        os.remove(os.path.join(backup_dir, file_to_delete))

if __name__ == "__main__":
    if not os.path.exists(BACKUP_DIR):
        os.makedirs(BACKUP_DIR)

    while True:
        create_backup(DB_NAME, BACKUP_DIR)
        cleanup_backups(BACKUP_DIR, NUM_TO_KEEP)
        time.sleep(INTERVAL_HOURS * 3600)