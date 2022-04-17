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
//#region socket
var _socket = io(location.host + ':3001', {
    path: '/gamesocket'
  });
//endregion
//#region connection info
var _gameID;
var _userPrivate;
var _userPublic;
var _oppPublic;
var _user;
var _opp;
//endregion
//#region game info
var _hand;
var _inHandLocal;
var _inHandOpp;
//endregion
//#region misc
var _DOMPergatory;
//endregion