/*
This file is part of IDK Does Kards.

IDK Does Kards is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

IDK Does Kards is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with IDK Does Kards.  If not, see <http://www.gnu.org/licenses/>.
*/
//#region includes
var express = require('express');
var router = express.Router();
var app = express();
var passport = require('passport');
var LocalStrategy = require('passport-local').Strategy;
var db = require('./../database/mysql');
var loki = require('lokijs');
var lokidb = new loki('metadata');
var multer  = require('multer');
var upload = multer({ dest: '../../uploads/' });
var nativ = require('./../../Game/game_wrapper');
var g = require('./../game');

var users = lokidb.addCollection('users');
//endregion
//#region passport
passport.use(new LocalStrategy(
  (username, password, done) => {
      db.login(username,password, (data) =>{
        if(data != false){
          data.Password = nativ.randIsaac();
          users.insert(data);
          return done(null,data);
        }
        else{
          return done(null,false,{message:"Incorrect usnername or password"})
        }
      });
      }

));

passport.serializeUser(function (user, done) {
  done(null, user);
});
passport.deserializeUser(function (user, done) {
  done(null, user);
});
//endregion
//#region homepage
router.get('/', function(req, res, next) {
  res.render('login');
});



router.get('/home', function(req, res, next) {
  //check db lokijs
  // if(req.session.cookie.time){
  //   req.session.cookie.time++;
  // }
  var data = verifyToken(req.session.passport.user.Username, req.session.passport.user.Password);
  res.render('index',data);
});

router.get('/cards', function(req, res, next) {
  var data = verifyToken(req.session.passport.user.Username, req.session.passport.user.Password);
  res.render('cardviewer', data);
});

router.get('/play', function(req, res, next) {
  var data = verifyToken(req.session.passport.user.Username, req.session.passport.user.Password);
  res.render('play', data);
});

router.get('/game', function(req, res, next) {
  res.render('game');
});


router.post('/login', passport.authenticate('local'), function(req,res){
    res.redirect("/home");
}
);
router.post('/login/register', function(req, res, next) {

  db.register(nativ.randUUID(),req.param('email'),req.param('username'),req.param('password'), (val) => {
    if(val){
    res.send(200);
    }else{
      res.send(401);
    }
  });
});
router.post('/editer',function(req,res,next){
  db.removeCard(req.param('cardId'),  (err) => {
      if(err){
          console.log(err);
      }
  });
  db.createCards(req.param('cardId'), req.param('name'), req.param('imageUrl'), req.param('cost'),req.param('attack'),req.param('defense'),req.param('type'),req.param('text'),(err) =>{
    if(err){
      console.log(err);
    }
  });
  res.end();
});
router.get('/editer', function(req, res, next){
  res.render('editer');
});
router.get('/register',function(req,res,next){
    res.render('register');
});
//endregion
//#region upload
router.post('/upload', upload.single('test'), function(req, res) {
  //create GUID
  let id = nativ.randUUID();
  let file = req.file;
  //Parse Card info
  //uplaod to db
  /*file.mv('path/' + GUID + '.idk', (err) => { //saves the file
    if (err)
      return res.status(500).send(err);

  });*/
  res.end();
});
//endregion
//#region API
router.get('/api/findMatch/:pid', function(req, res, next) {
  let id = req.params.pid;
});

router.get('/api/idToCard', function(req, res, next) {
  db.lookUpCard(req.query.id, (data) => {
    for(id in data){
      res.json(data[id]);
      break;
    }
  });
});

router.get('/api/cardNameToId', function(req, res, next) {
  //TODO
  console.log(req.query.card);
  res.json({id: '1'});
});


router.get('/match/matchfinder', function(req, res, next) {
  console.log(req.query.id);
  res.json({id: '1'});
});
//endregion
//#region Game API
router.get('/game/api/mana/:id', function(req, res, next) {
  //TODO
  console.log(req.params.id);
  res.json({local : {max : 10, cur: 5}, opp : {max: 10, cur: 10}});
});

router.get('/game/api/health/:id', function(req, res, next) {
  //TODO
  console.log(req.params.id);
  res.json({local : {cur: 20}, opp : {cur: 20}});
});

router.get('/game/api/hand/private/:id/:playerPrivate', function(req, res, next) {
  //TODO
  console.log(req.params.id + " " + req.params.playerPrivate);
  res.json(nativ.getHands(activeMatch)[0]);
});

router.get('/game/api/hand/public/:id/:playerPublic', function(req, res, next) {
  //TODO
  res.json({count : nativ.getHands(activeMatch)[1].length});
});
//endregion
//#region Admin API


router.get('/admin', function(req, res, next) {
  //get match info
  res.render('admin_panel', {p1: 'p1', p2: 'p2', id: 'error'});
});
//hacky but im kinda not feeling the post rn cause we are super behind
router.get('/admin/draw/:pid', function(req, res, next) {
 console.log(activeMatch + "  " + req.params.pid);
 nativ.drawCard(activeMatch, parseInt(req.params.pid));
 console.log(req.params.id);
 console.log(req.params.pid);
 g.update(activeMatch, 'hand');
 res.sendStatus(200);
});

router.get('/admin/start/', function(req, res, next) {
  activeMatch = nativ.startGame("p1", "p2", [ "b9f92a84-e09b-4415-8b5b-801ad64c171c", "b9f92a84-e09b-4415-8b5b-801ad64c171c", "b9f92a84-e09b-4415-8b5b-801ad64c171c" ], [ "b9f92a84-e09b-4415-8b5b-801ad64c171c", "b9f92a84-e09b-4415-8b5b-801ad64c171c", "b9f92a84-e09b-4415-8b5b-801ad64c171c" ]);
  console.log(activeMatch);
g.update(activeMatch, 'hand');  
  res.json({id: activeMatch});
 });

 function verifyToken (username, secret) {
  var temp = users.findOne({'Username': username});
  if( temp.Password == secret){
    return temp;
  }else{
    return undefined;
  }
 }
//endregion
module.exports = router;
