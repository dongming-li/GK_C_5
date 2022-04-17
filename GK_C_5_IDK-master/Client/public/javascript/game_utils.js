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

//#region sync API
/**
 * Sync mana bar with server
 */
function syncManaBars() {
    $.get("game/api/mana/" + _gameID, (data) => {
        updateLocalMana(data.local.max, data.local.cur);
        updateOppMana(data.opp.max, data.opp.cur);
    });
}

/**
 * Sync health with server
 */
function syncHealth() {
    $.get("game/api/health/" + _gameID, (data) => {
        updateLocalHealth(data.local.cur);
        updateOppHealth(data.opp.cur);
    });
}
/**
 * Sync hand with server
 */
function syncHand() {
    $.get("game/api/hand/private/" + _gameID + "/" + _userPrivate, (data) => {
        console.log(data);
        updateLocalHand(data);
    });
}

function syncOppHand() {
    $.get("game/api/hand/public/" + _gameID + "/" + _oppPublic, (data) => {
        //TODO
    });
}
//endregion
//#region helper methods
/**
* Updates local mana, DO NOT USE CALL syncManaBar instead
* 
* @param {int} max  - Max mana
* @param {int} cur  - cur mana
*/
function updateLocalMana(max, cur) {
    $('#local_mana_text').text(`${cur}/${max}`)
    $('#local_mana_bar').animate({ height: (cur / max * 100) + '%' }, 500);
}

/**
* Updates opp mana, DO NOT USE CALL syncManaBar instead
* 
* @param {int} max  - Max mana
* @param {int} cur  - cur mana
*/
function updateOppMana(max, cur) {
    $('#opp_mana_text').text(`${cur}/${max}`)
    $('#opp_mana_bar').animate({ height: (cur / max * 100) + '%' }, 500);
}

/**
* Updates local health, DO NOT USE CALL syncHealth instead
* 
* @param {int} max  - Max mana
* @param {int} cur  - cur mana
*/
function updateLocalHealth(cur) {
    $('#local_health').text(`${cur}`)
}

/**
* Updates opp health, DO NOT USE CALL syncHealth instead
* 
* @param {int} cur  - cur health
*/
function updateOppHealth(cur) {
    $('#opp_health').text(`${cur}`)
}

/**
* Updates current hand
* 
* @param {*} hand  - array of cards in hand
*/
function updateLocalHand(hand) {
    for (card in hand) {
        if (!isInHand(hand[card])) {
            idToCard(hand[card], (data) => {
                render('local_hand', renderCard(data));
            });
        }
    }
    _hand = hand;
}

/**
 * plays card in players hand
 * @param {*} cID 
 */
function playCardLocal(cID) {
    idToCard(cID, (data) => {
        render('local_field', renderCard(data));
    });
}

/**
 * plays card in players hand
 * @param {*} cID 
 */
function playCardOpp(cID) {
    idToCard(cID, (data) => {
        render('opp_field', renderCard(data));
    });
}
//endregion
//#region data manipulation helpers
/**
 * Checks if card is in hand already
 * @param {*} card 
 * @return {bool} card is currently in hand
 */

function isInHand(card) {
    for (c in _hand) {
        if (c === card) return true;
    }
    return false;
}

function launchIntoFullscreen(element) {
    if (element.requestFullscreen) {
        element.requestFullscreen();
    } else if (element.mozRequestFullScreen) {
        element.mozRequestFullScreen();
    } else if (element.webkitRequestFullscreen) {
        element.webkitRequestFullscreen();
    } else if (element.msRequestFullscreen) {
        element.msRequestFullscreen();
    }
}

function sleep(miliseconds) {
    var currentTime = new Date().getTime();
 
    while (currentTime + miliseconds >= new Date().getTime()) {
    }
 }
  //endregion
