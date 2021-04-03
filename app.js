const express = require('express');
const logger = require('morgan');
const videogames = require('./routes/interruptores') ;
const interruptores = require('./routes/interruptores');
const bodyParser = require('body-parser');
const mongoose = require('./config/database'); 
const app = express();

// Conectando a la base de datos de Mongo
mongoose.connection.on('error', console.error.bind(console, 'Error de conexion en MongoDB'));

app.use(logger('dev'));
app.use(bodyParser.urlencoded({extended: true}));
app.use(bodyParser.json());

app.get('/', function(req, res){
  res.json({"Proyecto WebAPI" : "API REST con NodeJS"});
});
// Rutas publicas
app.use('/interruptores', interruptores);

// Manejando errores HTTP 404 para solicitudes de contenido inexistente
app.use(function(req, res, next) {
 let err = new Error('Not Found');
    err.status = 404;
    next(err);
});
// Manejo de errores, respuestas con codigo HTTP 500, HTTP 404
app.use(function(err, req, res, next) {
 console.log(err);
 
  if(err.status === 404)
   res.status(404).json({message: "Not found"});
  else 
    res.status(500).json({message: "Error interno en el servidor!!"});
});
app.listen(3300, function(){
 console.log('El servidor ha sido inicializado: http://localhost:3000');
});