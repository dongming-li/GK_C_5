    var mysql  = require('mysql');  
    var SqlString = require('sqlstring');
    var passwordHash = require('password-hash');
    var connection = mysql.createConnection({     
     host     : 'mysql.cs.iastate.edu',       
     user     : 'dbu309gkc5',              
     password : '#@rtBf@d',       
     port: '3306',                   
     database: 'db309gkc5', 
    });

    connection.connect();
    /*
       
       
        3. lowerCase camel
    */
module.exports.login = (email, password, callback) => {
        connection.query("SELECT * FROM users", function (err, result) {
            if (err){
              console.log('[SELECT ERROR] - ',err.message);
              console.log(sql);
                return(false);
            }
            var user = result.filter((data) => {
                return(data.Email === email);
            });
            if (user.length === 1){
                if (passwordHash.verify(password, user[0].Password)){
                    callback(user[0]);
                }
            }
            callback(false);
            
    });
};
module.exports.getUsername=(email, callback) =>{
    connection.query(SqlString.format(`SELECT Username FROM users where Email = ? `,[email] ),function (err,result){
        if(err){

            console.log('[SELECT ERROR] - ',err.message);

            return (false);
        }
        callback(result[0].Username);
    });
};

module.exports.register = (UserId, email, username, password, callback) => {
    connection.query("SELECT * FROM users", function (err, result) {
        if (err){
            console.log('[SELECT ERROR -', err.message);
            callback(false);
        }
        var user = result.filter((data) => {
            return (data.Username === username || data.Email === email);
        });
        console.log(user);
        if (user.length > 0)  callback(false);
       
        console.log("insert");
        connection.query(SqlString.format( `INSERT INTO users(UserID , Email, Username, Password) VALUES (?, ?, ?, ?)`, 
        [UserId, email, username, passwordHash.generate(password)]), function(err, result) {
            console.log(err);
            console.log(result);
            callback(true);
        });
});
};

module.exports.lookUpCard = (id, callback) => {
    connection.query( SqlString.format(`select * from cards where CardID = ?`, id), function(err, result) {
        callback(result );
    });
};

module.exports.createCards = (CardID, Name, ImageUrl, Cost, Attack, Defense, Type, Text, callback) =>{
    connection.query(SqlString.format('insert into cards (CardID, Name, ImageUrl, Cost, Attack, Defense, Type, Text) values (?, ?, ?, ?, ?, ?, ?, ?)',
    [CardID, Name, ImageUrl, Cost, Attack, Defense, Type, Text]),function(err, result){
        if (err){
            console.log(" Message:" + err.message);
            callback( false);
        }else { 
            callback( true);
        }
    });
};
module.exports.removeCard =(CardID, callback) =>{
    connection.query(SqlString.format('delete from cards where CardID = ?',[CardID]),function(err, result){
        if (err){
            console.log(" Message:" + err.message);
            callback(false);
        }else {
            callback(true);
        }
    });
};
module.exports.userCreatedCards = (UserID, callback) => {
   connection.query(SqlString.format("select CardID from user_card where UserID=?",[UserID]),function(err, result){
       if (err){
        console.log(" Message:" + err.message);
       }else {
           callback(result);
       }
   });
};
module.exports.userDecks = (UserID, callback) => {
    connection.query(SqlString.format("select DeckID from  user_deck where UserId=?",[UserID]),function(err, result){
        if (err){
            console.log(" Message:" + err.message);
        }else { 
            callback(result);
        }
    });
};
module.exports.userAddDeck =(UserID, DeckID, callback) => {
    connection.query(SqlString.format("insert into user_deck (UserID, DeckID) values (?, ?)",[UserID, DeckID]),function(err, result){
        if (err){
            console.log(" Message:" + err.message);
            callback(false);
        }else {
            callback(result);
        }
    });
};
module.exports.userRemoveDeck = (DeckID, callback) => {
    connection.query(SqlString.format("delete from user_deck where deckID = ?",[DeckID]),function(err, result){
        if (err){
            console.log(" Message:" + err.message);
            callback(false);
        }else {
            callback(true);
        }
    });
};
module.exports.deckCards = (DeckID, callback)=>{
    connection.query(SqlString.format("select CardID ,Quantity from decks where deckID = ?",[DeckID]),function(err,reuslt){
        if (err){
            console.log(" Message:" + err.message);
        }else {
            callback(reuslt);
        }
    });
};
module.exports.deckAddCard = (DeckID, CardID, callback)=>{
    connection.query(SqlString.format("select Quantity from decks where deckID = ? and CardID= ?",[DeckID, CardID]),function(err,result){
        if (err){
            console.log(" Message:" + err.message);
            callback(false);
        }else {
            if (0 === result.length){
                connection.query(SqlString.format("insert into decks (DeckID, CardID, Quantity) values(?, ?, ?)",[DeckID, CardID, 1]),function(err, result2){
                    if (err){
                        console.log("Message:" + err.message);
                        callback(false);
                    }else {
                        callback(true);
                    }
                });
            }else {
                connection.query(SqlString.format("update decks set quantity = ? where deckID = ? and CardID=?",[result[0].Quantity+1, DeckID, CardID]),function(err, result2){
                    if (err){
                        console.log("Message:" + err.message);
                        callback(false);
                    }else {
                        callback(true);
                    }
                });
            }
        }
    });
};
module.exports.deckRmoveCard =(DeckID, CardID, callback) =>{
    connection.query(SqlString.format("select Quantity from decks where deckID = ? and CardID = ?",[DeckID, CardID]),function(err, result){
        if (err){
            console.log(" Message:" + err.message);
            callback(false);
        }else {
            if (0 === result.length){
                console.log("there is no this card in this deck");
                callback(false);
            }else {
                if (1 === result[0].Quantity){
                    connection.query(SqlString.format("Delete from decks where deckID = ? and CardID= ? ",[DeckID, CardID]),function(err, result2){
                        if (err){
                            console.log(" Message:" + err.message);
                            callback(false);
                        }else {
                            callback(true);
                        }
                    });
                }else {
                    connection.query(SqlString.format("update decks set Quantity = ? where deckID = ? and CardID = ?",[result[0].Quantity-1, DeckID, CardID]),function(err, result2){
                        if (err){
                            console.log(" Message:" + err.message);
                            callback(false);
                        }else {
                            callback(true);
                        }
                    });
                }
            }
        }
    });
};

module.exports.lookUpUUID = (Email, callback) =>
{
    connection.query(SqlString.format("select UserID from users where Email = ?",[Email]),function(err,result){
        callback(result);
    });
}