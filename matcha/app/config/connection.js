const mysql = require('mysql');

const pool = mysql.createPool({
  host     : 'status.hardfight.fr',
  user     : 'matcha',
  password : '',
  database : 'matcha'
});

module.exports = pool;
