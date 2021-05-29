const interruptorModel = require('../models/interruptores');

// Codificamos las operaciones que se podran realizar con relacion a los usuarios
module.exports = {
//Metodo para retornar todos los videojuegos registrados en la base de datos
obtenerData: async (req, res, next) => {
  let interruptores = [];
  await interruptorModel.find({}, function(err, Interruptores){
    if (err){
      next(err);
    } else{
      for (let interruptor of Interruptores) {
        interruptores.push(
          {
            id: interruptor._id, 
            nombre: interruptor.nombre, 
            estado: interruptor.estado,
            temperatura: interruptor.temperatura,
            fecha: interruptor.fecha
          }
          );
      }
      res.json({status:"Consulta correcta", message: "Lista de interruptores!!!", data:{Interruptores: interruptores}}); 
    }
   });
},

obtenerDataByRange: async (req, res, next) => {
  let interruptores = [];
  await interruptorModel.find({}, function(err, Interruptores){
    if (err){
      next(err);
    } else{
      for (let interruptor of Interruptores) {
        let fecha1 = new Date(req.params.fecha1);
        let fecha2 = new Date(req.params.fecha2);
        if(interruptor.fecha>=fecha1 && interruptor.fecha<=fecha2){
          interruptores.push(
            {
              id: interruptor._id, 
              nombre: interruptor.nombre, 
              estado: interruptor.estado,
              temperatura: interruptor.temperatura,
              fecha: interruptor.fecha,
              fecha1:new Date(req.params.fecha1),
              fecha2: req.params.fecha2
            }
          );
        }
        
      }
      res.json({status:"Consulta correcta", message: "Lista de interruptores!!!", data:{Interruptores: interruptores}}); 
    }
   });
},

//Metodo para crear algun registro nuevo
guardarData: async (req, res, next) => {
  let interruptor = {
    nombre: req.body.nombre,
    estado: req.body.estado,
    temperatura: req.body.temperatura,
    fecha: Date.now()
  }
  await interruptorModel.create(interruptor, function (err, result) {
      if (err) 
       next(err);
      else
       res.json({status: "Consulta correcta", message: "Interruptor agregado correctamente!!!", data: req.body});

    });
 },
}