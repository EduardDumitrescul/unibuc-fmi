var express = require('express');
var app = express();
app.use(express.static('html'));
app.use('/action',express.urlencoded({extended:true}));

var express = require('express');
var app = express();

app.use(express.static(__dirname));

app.get('/', function (req, res) {
    res.send('Hello World!');
});

app.get('/submit-message', function (req, res) {
    //res.send('Submit route !!');
    var name = req.query.inputName;
    var email = req.query.inputEmail;
    var message = req.query.inputMessage;
    console.log('Success');
    res.send(req.query);
    // res.redirect('index.html');
});


app.use(express.json());

// Store logged-in users in memory
let loggedInUsers = [];

// Login route
app.post('/login', (req, res) => {
  const { username, password } = req.body;

  // Check if the username and password are valid
  // Here, you would typically validate against a database or some other data source
  if (username === 'admin' && password === 'password') {
    // Add the user to the list of logged-in users
    loggedInUsers.push(username);

    res.json({ message: 'Login successful' });
  } else {
    res.status(401).json({ message: 'Invalid credentials' });
  }
});

// Logout route
app.post('/logout', (req, res) => {
  const { username } = req.body;

  // Remove the user from the list of logged-in users
  loggedInUsers = loggedInUsers.filter(user => user !== username);

  res.json({ message: 'Logout successful' });
});

// Check if a user is logged in
app.get('/loggedin', (req, res) => {
  const { username } = req.query;

  // Check if the user is in the list of logged-in users
  const isLoggedIn = loggedInUsers.includes(username);

  res.json({ isLoggedIn });
});


app.get('*', function(req, res){
  res.status(404).sendFile('404page.html', { root: '.' });
});

// // Handle 404 - Keep this as a last route
// app.use(function(req, res, next) {
//     res.status(404);
//     res.render('404page.html');
// });

app.listen(5500, function () {
    console.log('Example app listening on port 5500!');
});