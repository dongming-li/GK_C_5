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
//#region window init
$(window).ready(() => {
    initSocket();
    $('#concede').on('click', function () {
        return confirm('Are you sure?');
    });
    $('#pass_turn').on('click', function () {
        passTurn();
    });
    $("#chat_input").on('keyup', function (e) {
        if (e.keyCode == 13) {
            chat($("#chat_input").val());
            $("#chat_input").val('');
        }
    });
});
//endregion
//#region socket init
/**
 * initalizes socket to server, not to be confused with connection
 */
function initSocket() {

    _socket.on('Cred', (data) => {
        cred(data);
    });

    _socket.on('UserJoin', (data) => {
        userJoin(data);
    });

    _socket.on('StartMatch', (data) => {
        console.log('Start Match');
        startMatch();
    });

    _socket.on('PassTurn', (data) => {
        userJoin(data);
    });

    _socket.on('Draw', (data) => {
        draw(data);
    });

    _socket.on('Cast', (data) => {
        playerCast(data);
    });

    _socket.on('Update', (data) => {
        update(data);
    });

    _socket.on('Generic', (data) => {
        generic(data);
    });

    _socket.on('Chat', (data) => {
        console.log(data);
        addMsg(data.PID, data.msg);
    });


}

function login(u, p) {
    _socket.emit('Login', {username: u, pass: p});
    $('#connection_modal').css('display','block');
}

function waitForLogin() {
    console.log(_userPublic);
    _socket.emit('RequestUpdate', {id: _userPublic});
}

function chat(m) {
    _socket.emit('SendChat', {GID: _gameID,PID: _userPublic, Private: _userPrivate, msg: m});
}

function addMsg(u, m) {
    var uname = u == _userPublic ? 'You' : 'Opp';
    $('#msg_window').append(`${uname}: ${m}<br>`);
    $('#msg_window').scrollTop($('#msg_window')[0].scrollHeight);
}
//endregion