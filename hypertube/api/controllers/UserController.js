/**
 * UserController
 *
 * @description :: Server-side logic for managing users
 * @help        :: See http://sailsjs.org/#!/documentation/concepts/Controllers
 */
var bcrypt = require('bcryptjs');

module.exports = {

    create: function(req, res) {
        sails.log.debug(req.body);
        if (req.body.email == '' || req.body.firstname == '' || req.body.lastname == '' || req.body.pwd == '') {
            req.session.msg = 'Tout les champs requis ne sont pas remplis ou pas correctement.';
            return res.redirect('/auth/signup');
        }

        User.find({ email: req.body.email }).exec(function ( err, users) {
            if (err){
                sails.log.debug(err);
                return res.redirect('/auth/signup');
            }
            if (users.length === 0) {
                // if the mail not exist
                User.create(req.body).exec(function(err, result){
                    if (err) {
                        sails.log.debug(err);
                        req.session.msg = "One field is invalid, name should be more than 3 chars and the mail should be valid";;
                        return res.redirect('/auth/signup');
                    }
                    req.session.msg = 'Successfull !';
                    return res.redirect('/auth/login')
                });
            }
            else{
                // Err if mail already exist
                req.session.msg = 'Cet email est deja utilise';
                return res.redirect('/auth/signup');
            }
        })
    },
    
    my_profil : function (req, res){
        res.view('user/my_profil');
    },

    edit_picture : function(req,res){
        if(req.user){
            User.update({ id : req.session.user.id }, { image : req.param('picture') }).exec(function afterupdate(err, updated){
                if (err) {
                    req.session.msg = "The image you choose is not valid";
                    res.redirect('/my_profil');
                    return ;
                }
                req.session.user.image = req.param('picture');
                res.redirect('/my_profil');
            });
        }
        else
            res.redirect('/auth/login');
    },
    edit_info : function (req, res){
            User.update({ id : req.session.user.id }, 
                { firstname : req.param('firstname'),
                lastname : req.param('lastname'),
                email : req.param('email'),
                default_language : req.param('lang')})
                .exec(function (err, updated) {
                    if (err) {
                        sails.log.debug(err);
                        req.session.msg = "One field is invalid, name should be more than 3 chars and the mail should be valid";
                        res.redirect('my_profil');
                    }
                    else {
                        req.session.user.lastname = req.param('lastname');
                        req.session.user.firstname = req.param('firstname');
                        req.session.user.email = req.param('email');
                        req.session.user.default_language = req.param('lang');
                        res.redirect('my_profil');
                    }
            });
    },
    send_reset_pwd: function(req, res) {

        User.findOne({email: req.param('email')}).exec(function(err, user) {

            if (err) {return done(err);}
            if(user == null){
                req.session.msg = 'Mmmh, les informations ne concordent pas...';
                res.redirect('/lost_password');
                return;
            }
            else{
                if(req.param('firstname') == user.firstname && req.param('lastname') == user.lastname){
                    var token = Math.random()+'_'+user.email;
                    Token.create({ token : token}).exec(function afterupdate(err, updated){if(err){sails.log.debug(err)}});
                    token = new Buffer(token).toString('base64');
                    sails.hooks.email.send(
                        "reset_password",
                        {
                            recipientName: req.param('firstname'),
                            tokenLink: token,
                            senderName: "Admin"
                        },
                        {
                            to: req.param('email'),
                            subject: "Hi there"
                        },
                        function(err) {sails.log.debug(err || "Email for reset password sended !");}
                    );
                    req.session.msg = 'You will receved an email to reset you password.';
                    res.redirect('/auth/login');
                }
                else{
                    req.session.msg = 'Mmmh, les informations ne concordent pas...';
                    res.redirect('/lost_password');
                }

            }
        });
    },
    reset_pwd: function (req, res) {
        var base64regex = /^([0-9a-zA-Z+/]{4})*(([0-9a-zA-Z+/]{2}==)|([0-9a-zA-Z+/]{3}=))?$/;
        if(base64regex.test(req.param('token'))) {
            var token = new Buffer(req.param('token'), 'base64').toString('utf8');
            Token.findOne({token : token}).exec(function(err, returnToken){
                if(err){
                    sails.log.debug(err);
                    res.redirect('/auth/login');
                }
                if(!returnToken){
                    req.session.msg = 'Not a valid token.';
                    res.redirect('/auth/login');
                }
                else {
                    var email = token.split('_');
                    req.session.tmp_email = email[1];
                    Token.destroy({token : token}).exec(function(err, result){if(err){sails.log.debug(err)}})
                    res.view('user/new_password');
                }
            })
        }
        else {
            req.session.msg = 'Not a valid token.';
            res.redirect('/auth/login');
        }
    },
    new_pwd : function (req, res) {
        var pwd = req.param('password');
        if (req.session.tmp_email == undefined || pwd == undefined || pwd.length < 8) {
            req.session.msg = 'The password you tried to set is not valid (min 8 chars)';
            return res.redirect('/auth/login');
        }
        bcrypt.genSalt(10, function(err, salt) {
            bcrypt.hash(pwd, salt, function (err, hash) {
                if (err) {
                    sails.log.debug(err);
                    req.session.msg = 'Mmmmh pour une raison obscure, le hashage du mdp à echoué';
                    return res.view('/auth/login');
                }
                else {
                    pwd = hash;
                    User.update({email : req.session.tmp_email }, {pwd: pwd}).exec(function (err, result){
                        if(err) {
                            sails.log.debug(err);
                            req.session.msg = 'The password is not valid';
                            return res.view('/auth/login');
                        } else {
                            req.session.tmp_email = null;
                            req.session.msg = 'Update successfull';
                            res.redirect('/auth/login');
                        }
                    });
                }
            })
        });
    },

    findOne: function (req, res) {
        var id = req.params.id;

        if (id == undefined)   
            return res.notFound();

        User.find({ id: id }).exec(function (err, records) {
            if (err || records.length == 0)
                return res.notFound();
            else {
                res.view('user/other_profil', { user: records[0] });
            }
        });
    } 
};

