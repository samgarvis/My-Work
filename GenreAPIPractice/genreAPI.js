const config = require('config');
const Joi = require('joi');
const express = require('express');
const app = express();
const genres = require('./routes/genres');
const home = require('./routes/home');


app.set('view engine', 'pug');
app.set('views', './views');

var lastID = 0;

app.use(express.json());
app.use('/api/genres', genres);
app.use('/', home);

console.log('Application Name: ' + config.get('name'));
console.log('Mail Server: ' + config.get('mail.host'));
console.log('Mail Password: ' + config.get('mail.password'));

const port = process.env.PORT || 3000;
app.listen(port, () => console.log(`Listening on port ${port}...`));


