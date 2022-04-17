//#region includes
var nativ = require('./../Game/game_wrapper');
//#endregion
//#region vars
//{id: Pid, private: PPrivate, gid: GameID, opp: opId}
var players = {};
var waiting =  [];
//#endregion
//#region constructor
/**
 * Creates new lobby
 */
//#endregion
//#region methods

/**
 * Finds a lobby or puts you in waiting queue
 * @param {*} pid 
 */
module.exports.findLobby = (pid) => {
    console.log('Connecting to lobby: ' + pid[0].UserID);
    players[pid[0].UserID] = {private: nativ.randUUID(), gid: null}
    if(waiting.length > 0) {
        let otherP = waiting.pop();
        let gid = nativ.startGame(pid[0].UserID, otherP[0].UserID, [ "b9f92a84-e09b-4415-8b5b-801ad64c171c", "b9f92a84-e09b-4415-8b5b-801ad64c171c", "b9f92a84-e09b-4415-8b5b-801ad64c171c" ], [ "b9f92a84-e09b-4415-8b5b-801ad64c171c", "b9f92a84-e09b-4415-8b5b-801ad64c171c", "b9f92a84-e09b-4415-8b5b-801ad64c171c" ]);
        players[pid[0].UserID].gid = gid;
        players[pid[0].UserID].opp = otherP[0].UserID;
        players[otherP[0].UserID].gid = gid;
        players[otherP[0].UserID].opp = pid[0].UserID;
        console.log('Match found: ' + pid[0].UserID + ' ' + otherP[0].UserID + ' ' + gid);
        return true;
    } else {
        waiting.push(pid);
        console.log('Moved to waiting: ' + pid[0].UserID);
        return false;
    }
};

/**
 * Checks if you have found a lobby yet
 * @param {*} pid 
 * @param {*} callback 
 */
module.exports.updateLobby = (pid, callback) => {
    if(undefined == players[pid]) return undefined;
    if(players[pid].gid == null) return false;
    callback(players[pid], pid);
};

/**
 * Authenticates pid and privateid
 * @param {*} pid 
 * @param {*} private 
 */
module.exports.auth = (pid, private) => {
    if(undefined == players[pid]) return undefined;
    return players[pid].private == private;
};

/**
 * gets player info
 * @param {*} pid 
 */
module.exports.getPlayer = (pid) => {
    players[pid];
    
};
//#endregion