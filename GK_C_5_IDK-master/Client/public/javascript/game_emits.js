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

//#region socket emits

  /**
   * Requests to change lobby
   *
   * @param {string} lobbyId - Name of lobby to join
   * @param {string} password - lobby password
   */
function requestLobby(lobbyId, password){
    _socket.emit('RequestLobby', {user: _userPublic, lobby: lobbyId});
}
/**
 * Passes turn
 */
function passTurn() {
    _socket.emit('PassTurn');
}

/**
 * Cast
 * @param {ID} cardID - Id of casted card
 * @param {target[]} t - array of targets
 */

 function cast(cardID, t) {
     _socket.emit('Cast', {gID: _gameID, public: _userPublic, private: _userPrivate, cID: cardID, target: t});
 }
 //endregion