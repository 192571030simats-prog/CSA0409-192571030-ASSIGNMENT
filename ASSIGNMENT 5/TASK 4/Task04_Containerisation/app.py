from flask import Flask, jsonify
app = Flask(__name__)

@app.get("/")
def home():
    return jsonify(service="University Result Portal", status="running")

@app.get("/health")
def health():
    return jsonify(status="healthy"), 200
