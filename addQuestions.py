import requests
import sqlite3
import random
import html

# get trivia data
def get_questions(amount=10):
    url = f"https://opentdb.com/api.php?amount={amount}&type=multiple&encode=url3986"
    response = requests.get(url)
    data = response.json()
    return data['results']

# Setup DB (create table if not exist)
def setup_db():
    conn = sqlite3.connect('TriviaDB.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS questions (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            question TEXT,
            answer_1 TEXT,
            answer_2 TEXT,
            answer_3 TEXT,
            answer_4 TEXT,
            correct_answer INTEGER,
            difficulty TEXT,
            category TEXT
        );
    ''')
    conn.commit()
    return conn

# Insert into DB
def insert_questions(conn, questions):
    cursor = conn.cursor()
    for q in questions:
        question = html.unescape(q['question'])
        correct = html.unescape(q['correct_answer'])
        incorrect = [html.unescape(ans) for ans in q['incorrect_answers']]
        difficulty = q['difficulty']
        category = q['category']

        # add correcr answer to the answers and shuffle all the answers after
        options = incorrect + [correct]
        random.shuffle(options)
        correct_index = options.index(correct) + 1

        cursor.execute('''
            INSERT INTO questions (
                question, answer_1, answer_2, answer_3, answer_4,
                correct_answer, difficulty, category
            ) VALUES (?, ?, ?, ?, ?, ?, ?, ?)
        ''', (
            question,
            options[0],
            options[1],
            options[2],
            options[3],
            correct_index,
            difficulty,
            category
        ))

    conn.commit()

# Main
if __name__ == "__main__":
    conn = setup_db()
    questions = get_questions(10)
    insert_questions(conn, questions)
    print("Inserted questions.")
    conn.close()
