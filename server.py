from sqlite3.dbapi2 import connect
from flask import Flask, request, jsonify
import sqlite3

import datetime

app = Flask(__name__)

get_water = "SELECT temp, humi FROM farm WHERE type=\"water\" ORDER BY date DESC LIMIT 1"
get_ground = "SELECT temp, humi FROM farm WHERE type=\"ground\" ORDER BY date DESC LIMIT 1"
add_environ = "INSERT INTO farm (temp, humi, type, date) VALUES (?, ?, ?, ?)"


@app.route('/environ', methods=['POST'])
def save_environ():
    c = conn.cursor()

    value = request.json

    now = datetime.datetime.now()

    c.execute(add_environ, (value["temp"], value["humi"], value["type"], str(now)))
    conn.commit()

    return "succes!"

@app.route('/environ/<type>')
def get_environ(type):
    c = conn.cursor()
    if type == "water":
        result = c.execute(get_water).fetchall()
        return jsonify({"temp" : result[0][0],
                    "humi" : result[0][1]})
    elif type == "ground":
        result = c.execute(get_ground).fetchall()
        return jsonify({"temp" : result[0][0],
                    "humi" : result[0][1]})
        
if __name__ == "__main__":
    conn = sqlite3.connect('farm.db', check_same_thread=False)
    app.run(host='127.0.0.1', port=8080, debug=True)