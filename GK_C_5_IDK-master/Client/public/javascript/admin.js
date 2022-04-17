var id;

function joinMatch() {
   let id = $('#matchId').val();
   window.location.href = '/admin/' + id;
}

function forceDraw(player) {
    $.get(window.location.href + '/draw/' + player);
}

function startGame() {
    $.get(window.location.href + '/start/', (data) => {
        id = data.id;
        $('#mid').text(id);
    });
}