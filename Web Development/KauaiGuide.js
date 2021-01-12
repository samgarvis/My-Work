const express = require('express');
const app = express();
const path = require('path');

app.use('/assets', express.static('assets'));

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname+'/index.html'));
});

app.get('/index', (req, res) => {
    res.sendFile(path.join(__dirname+'/index.html'));
});

app.get('/Sites', (req, res) => {
    res.sendFile(path.join(__dirname+'/Sites.html'));
});

app.get('/Transportation', (req, res) => {
    res.sendFile(path.join(__dirname+'/Transportation.html'));
});

app.get('/Flights', (req, res) => {
    res.sendFile(path.join(__dirname+'/Flights.html'));
});

app.get('/Camping', (req, res) => {
    res.sendFile(path.join(__dirname+'/Camping.html'));
});


const port = process.env.PORT || 3000;
app.listen(port, () => console.log(`Listening on port ${port}...`));


