// Cargamos el modulo express
const express = require('express');
const router = express.Router();
// Cargamos el controlador 
const interruptorContoller = require('../api/controllers/interruptores');
// Especificamos nuestras rutas teniendo en cuenta los metodos creados en nuestro controlador, y especificando que seran rutas que usaran el metodo POST
router.get('/', interruptorContoller.obtenerData);
router.get('/:fecha1/:fecha2', interruptorContoller.obtenerDataByRange);
router.post('/', interruptorContoller.guardarData);
module.exports = router;