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


//#region test data
var testData = {id: 1, cred: {User: {Name : 'Will', Public: '1', Private: '3'}, Opp :{Name: 'not will', Public: '2'}}};
//endregion
//#region connection

  /**
   * Function to be called when user joins server, game info returned
   *
   * @param {object} data - Server data
   */
function cred(data){
    _user = data.User.Name;
    _opp = data.Opp.Name;
    _userPrivate = data.User.Private;
    _userPublic = data.User.Public;
    _oppPublic = data.Opp.Public;
    $('#local_name').text(_user);
    $('#opp_name').text(_opp);
}

  /**
   * Function to be called when UserJoin event recieved
   *
   * @param {object} data - Server data
   */
function userJoin(data) {
    console.log('User Joined: ' + data);
}
//endregion
//#region match begin
function startMatch() {
    $('#connection_modal').css('display','none');
    syncManaBars();
    syncHealth();
    syncHand();
    launchIntoFullscreen(document.documentElement);
}
//endregion
//#region helper methods
/**
 * Called when draw event occurs
 * 
 * @param {*} data 
 */
function draw(data) {
    if(data.player === _userPublic) {
        syncHand();
    }else {

    }
}

/**
 * Update given value
 * 
 * @param {*} data
 */
function update(data) {
    switch(data) {
        case 'mana' : syncManaBars();
        break;
        case 'health' : syncHealth();
        break;
        case 'hand': syncHand();
        break;
        default : return 'error: invalid data';
        break;
    }
}

/**
 * Update given value
 * 
 * @param {*} data
 */
function generic(data) {
    console.log(data);
    switch(data.type) {
        case 'private' : _userPrivate = data.val;
        $('#PrivID_field').text(_userPrivate);
        break;
        case 'public' : _userPublic = data.val[0].UserID;
        $('#PID_field').text(_userPublic);
        break;
        case 'oppPublic': _oppPublic = data.val;
        $('#OppID_field').text(_oppPublic);
        break;
        case 'gameId' : $('#GID_field').text(data.val);
        _gameID = data.val;
        break;
        default : return 'error: invalid data';
        break;
    }
}


/**
 * Casts card from server
 * @param {*} data 
 */
function playerCast(data) {
    if(data.player == _userPublic) {
        playCardLocal(data.cID);
    }else if(data.player == _oppPublic) {
        playCardOpp(data.cID);
    }
}
//endregion