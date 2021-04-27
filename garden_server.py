import dash
import dash_core_components as dcc
import dash_html_components as html
from dash.dependencies import Input, Output

import pandas as pd
import plotly.express as px

import init

external_stylesheets = ['https://codepen.io/chriddyp/pen/bWLwgP.css']

app = dash.Dash(__name__, external_stylesheets=external_stylesheets)
app.layout = html.Div(
    html.Div([
        html.H4('Garden Monitor Live Feed'),
        dcc.Graph(id='live-update-graph'),
        dcc.Graph(id='live-update-graph2'),
        dcc.Graph(id='live-update-graph3'),
        dcc.Graph(id='live-update-graph4'),
        dcc.Graph(id='live-update-graph5'),
        dcc.Graph(id='live-update-graph6'),
        dcc.Interval(
            id='interval-component',
            interval=1*10000, # in milliseconds
            n_intervals=0
        )
    ])
)


# Multiple components can update everytime interval gets fired.
@app.callback(Output('live-update-graph', 'figure'),
              Output('live-update-graph2', 'figure'),
              Output('live-update-graph3', 'figure'),
              Output('live-update-graph4', 'figure'),
              Output('live-update-graph5', 'figure'),
              Output('live-update-graph6', 'figure'),
              [Input('interval-component', 'n_intervals')])
def update_graph_live(n):
    last_line = ''
    with open(init.stemp_path) as f:
        for line in f:
            pass
        last_line = line
    df = pd.read_csv(init.stemp_path)
    lines = last_line.split(",")
    fig = px.line(df.tail(100), x='datetime', y='temperature', title='Temperature Sensor - '+lines[0]+", "+lines[1].strip()+" (F)")
    
    last_line2 = ''
    with open(init.humidity_path) as f:
        for line in f:
            pass
        last_line2 = line
    df2 = pd.read_csv(init.humidity_path)    
    lines2 = last_line2.split(",")
    fig2 = px.line(df2.tail(100), x='datetime', y='humidity', title='Air Humidity - '+lines2[0]+", "+lines2[1].strip()+"%")
    
    last_line3 = ''
    with open(init.rtemp_path) as f:
        for line in f:
            pass
        last_line3 = line
    df3 = pd.read_csv(init.rtemp_path)    
    lines3 = last_line3.split(",")
    fig3 = px.line(df3.tail(100), x='datetime', y='temperature', title='CPU Temperature - '+lines3[0]+", "+lines3[1].strip()+" (C)")
    last_line3 = ''
    
    with open(init.atemp_path) as f:
        for line in f:
            pass
        last_line4 = line
    df4 = pd.read_csv(init.atemp_path)    
    lines4 = last_line4.split(",")
    fig4 = px.line(df4.tail(100), x='datetime', y='temperature', title='Air Temperature - '+lines4[0]+", "+lines4[1].strip()+" (F)")

    with open(init.moisture_path) as f:
        for line in f:
            pass
        last_line5 = line
    df5 = pd.read_csv(init.moisture_path)    
    lines5 = last_line5.split(",")
    fig5 = px.line(df5.tail(100), x='datetime', y='moisture', title='Moisture Sensor- '+lines5[0]+", "+lines5[1].strip())
    
    with open(init.light_path) as f:
        for line in f:
            pass
        last_line6 = line
    df6 = pd.read_csv(init.light_path)    
    lines6 = last_line6.split(",")
    fig6 = px.line(df6.tail(100), x='datetime', y='lux', title='Light Sensor- '+lines6[0]+", "+lines6[1].strip() +" lx")
    
    return fig, fig5, fig6, fig4, fig2, fig3


if __name__ == '__main__':
    app.run_server(debug=True,port=8080,host='0.0.0.0')
