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

//#region rendering

/**
 * Generates HTML for any given card
 *
 * @param {json} card - json value of card.
 */
function renderCard(card) {
    return `
<div class="game_card" id="${card.CardID}">
<div class="card_top">
  ${card.Name}
</div>
<div class="card_middle" style="background-image: url('${card.ImageUrl}')">
  <div class="card_side_bar">
    <div class="card_mana_cost">
    ${card.Cost}
    </div>
    <div class="card_attk">
    ${card.Attack}
    </div>
    <div class="card_def">
    ${card.Defense}
    </div>
  </div>
</div>
<div class="card_stat">
    ${card.Type}
</div>
<div class="card_desc">
  <p>${card.Text}</p>
</div>
</div>
`
}

/**
 * @return {*} returns static card back
 */
function renderCardBack() {
    return `
    <div>
     CardBack
    <div>
    `
}

/**
 * Renders HTML block
 *
 * @param {string} appendTo - div to append to.
 * @param {string} code - code block to append.
 */
function render(appendTo, code) {
    $('#' + appendTo).append(code);
}

/**
 * 
 * @param {cID} id 
 * 
 * @return
 */
function derender(id) {
    return $('#' + id).detach();
}
//endregion
//#region API
/**
 * gets card name from the ID
 *
 * @param {id} id - id of Card.
 * @param {callback} callback - Callback.
 */
function idToCard(id, callback) {
    $.get("/api/idToCard?id=" + id, function (data) {
        callback(data);
    });
}
/**
 * gets card ID from the name
 *
 * @param {string} cardName - Name of Card.
 * @param {callback} callback - Callback.
 */
function cardNameToId(cardName, callback) {
    $.get("/api/idToCard?card=" + cardName, function (data) {
        callback(data);
    });
}
//endregion