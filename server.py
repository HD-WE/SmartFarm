from sqlite3.dbapi2 import connect
from flask import Flask, request, jsonify
import sqlite3

import datetime

app = Flask(__name__)

get_enviorn = "SELECT temp, humi FROM farm ORDER BY date DESC LIMIT 1"
get_all = "SELECT * from farm"
add_environ = "INSERT INTO farm (temp, humi, type, date) VALUES (?, ?, ?, ?)"


@app.route('/environ', methods=['POST', 'GET'])
def environ():
    c = conn.cursor()
    if request.method == 'GET':
        result = c.execute(get_enviorn).fetchall()
        return jsonify({"temp" : result[0][0],
                    "humi" : result[0][1]})
    elif request.method == 'POST':
        value = request.json

        print(value["temp"])

        now = datetime.datetime.now()

        c.execute(add_environ, (value["temp"], value["humi"], value["type"], str(now)))
        conn.commit()

        return "succes!"
        
if __name__ == "__main__":
    conn = sqlite3.connect('farm.db', check_same_thread=False)
    app.run(host='127.0.0.1', port=8080, debug=True)