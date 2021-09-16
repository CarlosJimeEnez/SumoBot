from io import open
from os import read
import paho.mqtt.client as mqtt 

'''MQTT:''' 
# def on_connect(client, userdata, flags, rc):
#     print("Connected with result code "+str(rc))
#     client.subscribe("$SYS/#")

def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

def read_valor_1():
    file = open("archivo.txt","r+")
    slider = file.read()
    return slider

def read_valor_2():
    file = open("archivo_1.txt","r+")
    slider = file.read()
    return slider

client = mqtt.Client()
# client.on_connect = on_connect
client.on_message = on_message

#Se especifica el servidor donde se va a conectar: 
client.connect("192.168.100.32", 1883, 60)

velocidad = {
    "slider_1" : 0,
    "Topic": "Coche", 
}
sentido = {
    "slider_2":0,
    "Topic": "Coche/Sentido",
}

valores = [velocidad,sentido]

while True:
    for valor in valores: 
        if valor == velocidad:
            velocidad["slider_1"] = read_valor_1()
            print(velocidad)
        if valor == sentido: 
            sentido["slider_2"] = read_valor_2()
            print(sentido) 
    client.publish("Coche",velocidad["slider_1"])
    client.publish("Coche/Sentido",sentido["slider_2"])
    client.loop()
