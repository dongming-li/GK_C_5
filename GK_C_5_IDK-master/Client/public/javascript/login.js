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
    $('#login').submit(function (e) {
        e.preventDefault();
        $.ajax({
            url: '/login',
            type: 'post',
            data: { username: $('#email').val(), password: $('#pass').val() },

            success: function () {
                window.location.href = "/home";
            }
        });
    });
});
//endregion