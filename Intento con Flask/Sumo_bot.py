from os import stat
from flask import Flask, app, render_template, request, Response
from time import sleep 
from io import open
import json 

#Prueba con JSON
def send_data_1(data_1,data_2):         
    data = {
        "Vuelta": data_2,
        "Media_vuelta": data_1
    }
    with open ("myfile.json","w") as j : 
        json.dump(data,j)
#    

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

# @app.route("/Media_vuelta",methods = ['POST'])
# def Media_vuelta(): 
#     data_1 = request.form["Media_vuelta"]
#     data_2 = 0
#     send_data_1(data_1,data_2)
#     data_1 = 0 
#     data_2 = 0 
#     send_data_1(data_1, data_2)
#     return render_template('index.html')

# @app.route("/Vuelta", methods = ['POST'])
# def Vuelta(): 
#     data_2 = request.form["Vuelta"]
#     data_1 = 0
#     send_data_1(data_1,data_2)
#     send_data_1(data_1,data_2)
#     return render_template('index.html')

if __name__ == "__main__": 
    app.debug = True 
    app.run(host='0.0.0.0')
      
       

