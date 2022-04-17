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
const io = require('socket.io')();
var lobby = require('./lobby');
var db = require('./database/mysql');
//endregion
//#region config
io.path('/gamesocket');
io.listen(3001);
//endregion
//#region declaration
io.on('connection', function (socket) {
  /* Init */
  io.to(socket.id).emit('Cred', { User: { name: 'local', id: socket.id }, Opp: { name: 'opp' } });

  socket.on('SendChat', (data) => { 
    console.log(data);
      io.to(data.GID).emit('Chat', {PID: data.PID,msg: data.msg});
  });

  socket.on('Login', (data) => {
    db.login(data.username, data.pass, (succ) => {
      if (succ) {
        db.lookUpUUID(data.username, (id) => {
        generic(socket.id, { type: 'public', val: id});
        socket.join(id[0].UserID);
        lobby.findLobby(id);
        lobby.updateLobby(id, (player) => {
          generic(id, { type: 'private', val: player.private });
          generic(id, { type: 'gameId', val: player.gid });
          generic(id, { type: 'oppPublic', val: player.opp });
        })
      });
      }
    });
  });
  
  socket.on('RequestUpdate', (data) =>
  {
    lobby.updateLobby(data.id, (player) => {
      console.log(player);
      generic(data.id, { type: 'private', val: player.private });
      generic(data.id, { type: 'gameId', val: player.gid });
      generic(data.id, { type: 'oppPublic', val: player.opp });
      socket.join(player.gid);
      io.to(player.gid).emit('StartMatch', {});
    })
  });

  /* general */
  socket.on('RequestLobby', (data) => {
    socket.join(data.lobby);
    io.to(data.lobby).emit('UserJoin', data.user);
  });

  /* game */
  socket.on('PassTurn', () => {
    //TODO
    console.log('pass turn');
  });

  socket.on('Cast', (data) => {
    cast(data, (validate) => {
      if (validate) {
        io.to(data.gID).emit('Cast', { cID: data.cID, target: data.target });
      }
    });
  });
});
//endregion
//#region helper methods
/**
 * Called on cast, callback returns if cast can happen
 * @param {*} data 
 * @param {*} callback 
 */
function cast(data, callback) {
  //call c++
  callback(true);
}


/* General Game API calls */
/**
 * Update given type, to be called by c++
 * @param {*} gID 
 * @param {*} type 
 */
function update(gID, type) {
  io.to(gID).emit('Update', type);
}

/**
 * Update given type, to be called by c++
 * @param {*} gID 
 * @param {*} type 
 */
function generic(pid, type) {
  io.to(pid).emit('Generic', type);
}


//endregion
module.exports.update = update;
