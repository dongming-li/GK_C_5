NAME:  
    createCards
PARAMETER:
    UserId,CardName,ImageUrl,Cost,Attack,Defense,Type,Text,callback
DESCRIPTION:
    This function will create a new card.
RETURN VALUE:
    true for success, false for fail.
=====================================================================
NAME:
    removeCard
PARAMETER:
    CardId,callback
DESCRIPTION:
    This fuction will remove the card from the database forevery
RETURN VALUE:
    true for success, false for fail
=====================================================================
NAME:
    userCreatedCards
PARAMETER:
    UserId,callback
DESCRIPTION:
    This function will return the card created by this user
RETURN VALUE:
    An array of the cards created by this user.
=====================================================================
NAME: 
    userDecks
PARAMETER:
    UserId,callback
DESCRIPTION:
    This fucntion will return what deck this user have
RETURN VALUE:
    An array of the deck id
=====================================================================
NAME:
    userAddDeck
PARAMETER:
    UserId,callback
DESCRIPTION:
    This fucntion will create a new deck for the user
RETURN VALUE:
    true for success, false for fail
=====================================================================
NAME:
    userRemoveDeck
PARAMETER:
     DeckId,callback
DESCRIPTION:
    This fucntion will remove a deck from a user
RETURN VALUE:
    true for success, false for fail
=====================================================================
NAME: 
    deckCards
PARAMETER:
    Deck's DeckId,callback
DESCRIPTION:
    This function will return what cards this deck includes
RETURN VALUE:
    An array of cards(including card.id card.num)
=====================================================================
NAME:
    deckAddCard
PARAMETER:
    CardId, DeckId,callback
DESCRIPTION:
    This function will add a card to a deck
RETURN VALUE:
    true for success, false for fail.
=====================================================================
NAME:
    deckRemoveCard
PARAMETER:
    CardId, DeckId,callback
DESCRIPTION:
    This function will remove a card from a deck
RETRUN VALUE:
    true for success, false for fail.
=====================================================================
