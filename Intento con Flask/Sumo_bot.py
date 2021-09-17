from os import stat
from flask import Flask, app, render_template, request, Response
from time import sleep 
from io import open

def send_valor_1(variable): 
    file = open("archivo.txt","w")
    file.write(variable)
    file.close()
    print(f"{variable}")

def send_valor_2(variable): 
    file = open("archivo_1.txt","w")
    file.write(variable)
    file.close()
    print(f"{variable}")
###
app = Flask(__name__)
@app.route("/")
def index(): 
    return render_template('index.html')

@app.route("/GO", methods = ["POST"])
def control(): 
    velocidad= request.form["Button"]
    send_valor_1(velocidad)
    
    return Response(status=200)

@app.route("/Righ_andLeft", methods = ["POST"])
def Righ_andLeft(): 
    Righ_andLeft = request.form["Righ_andLeft"]
    send_valor_2(Righ_andLeft)
    return Response(status = 200)

@app.route("/Media_vuelta",methods = ['POST'])
def Media_vuelta(): 
    Media_vuelta = request.form["media_vuelta"]
    print(f"{Media_vuelta}")

if __name__ == "__main__": 
    app.debug = True 
    app.run(host='0.0.0.0')
      
       

