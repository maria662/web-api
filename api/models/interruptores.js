// Cargamos el módulo de mongoose
const mongoose = require('mongoose');
//Definimos los esquemas
const Schema = mongoose.Schema;
// Creamos el objeto del esquema con sus correspondientes campos
const interruptorSchema = new Schema({
	nombre: {
		type: String,
		trim: true,  
		required: true,
	},
	estado:{
		type: Boolean,
		required: true,	
	},
	temperatura: {
		type: Number,
		required: true
	},
	fecha: {
		type: Date,
		required: true
	}
});
// Exportamos el modelo para usarlo en otros ficheros
module.exports = mongoose.model('Interruptor', interruptorSchema);
