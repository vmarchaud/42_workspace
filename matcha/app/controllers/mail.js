var nodemailer 	= require('nodemailer');

// config nodemailer
var smtpConfig = {
	host: 'debugmail.io',
    port: 25,
    auth: {
        user: 'thisismac47@gmail.com',
        pass: 'aa2d0fb0-2993-11e6-bc1b-f1b17bab5bbb'
    },
	tls: {rejectUnauthorized: false},
};

var transporter = nodemailer.createTransport(smtpConfig);

module.exports = transporter;