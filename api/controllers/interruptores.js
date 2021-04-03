const interruptorModel = require('../models/interruptores');

// Codificamos las operaciones que se podran realizar con relacion a los usuarios
module.exports = {
//Metodo para retornar todos los videojuegos registrados en la base de datos
async obtenerData: function(req, res, next) {
  let interruptores = [];
  await interruptorModel.find({}, function(err, Interruptores){
    if (err){
      next(err);
    } else{
      for (let interruptor of Interruptores) {
        interruptores.push({id: interruptor._id, nombre: interruptor.nombre, estado: interruptor.estado});
      }
      res.json({status:"Consulta correcta", message: "Lista de interruptores!!!", data:{Interruptores: interruptores}}); 
    }
   });
},

//Metodo para crear algun registro nuevo
async guardarData: function(req, res, next) {
  await interruptorModel.create(req.body, function (err, result) {
      if (err) 
       next(err);
      else
       res.json({status: "Consulta correcta", message: "Interruptor agregado correctamente!!!", data: req.body});

    });
 },
}