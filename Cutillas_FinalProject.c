#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct card_s { //card structure
	char suit;
	int face;
	struct card_s *listp;
} card;

card* CreateDeck(card *headp) { //creates an organized deck
	int i = 1; //counter
	int j = 0;
	char ctemp = 'c'; //temporary card suit storing, init to clubs
	card *current = headp, *temp, *tail = NULL; //all pointers needed for linked list

	temp = (card *)malloc(sizeof(card)); //
	temp->face = -1;                     //
	temp->suit = 'o';                    //
	headp = temp;                        // Adds 1st node: dummy head
	tail = temp;                         //
	tail->listp = NULL;                  //
	
	for (j = 0; j < 4; j++) { //for the 4 different suits
		if (j == 1) { //ignored on first run since j will be 0
			ctemp = 's'; //goes to spades next
		}
		else if (j == 2) {
			ctemp = 'h'; //then hearts
		}
		else if (j == 3) {
			ctemp = 'd'; //and finally diamonds
		}
		
		for (i = 1; i <= 13; i++) { //numbers 1-10 and 11=Jack, 12=Queen, 13=King
			temp = (card *)malloc(sizeof(card)); //allocates needed memory to temp
			temp->face = i; //temp is assigned card number
			temp->suit = ctemp; //and suit
			if (headp == NULL) { //only for first loop
				headp = temp;
			}
			else {
				tail->listp = temp; //adds temp to the end of the list 
			}
			tail = temp;
			tail->listp = NULL;
		}
	}

	temp = (card *)malloc(sizeof(card)); //
	temp->face = 100;                    //
	temp->suit = 'j';                    //
	tail->listp = temp;                  // Adds 1 last card: Joker, w face value 100 & suit j
	tail = temp;                         //
	tail->listp = NULL;                  //

	return headp;
}

card* ShuffleCard(card *headp, int size) {
	card *current = (card *)malloc(sizeof(card));
	card *swap = (card *)malloc(sizeof(card));
	card *temp;
	int j = 0;
	int num = 0;
	srand((int)time(0));
	
	current = headp->listp; //skipping dummy head
	swap = headp->listp; //skipping dummy head

	while (current->listp != NULL)
	{
		temp = (card *)malloc(sizeof(card)); //allocates memory to temp
		swap = headp->listp; //reinitialized to beginning every loop
		num = rand() % size; //gets random number within deck size
		for (j = 0; j < num; j++) { //cycles through deck until random num
			swap = swap->listp; 
		}

		temp->face = current->face; //assigns current's values to temp
		temp->suit = current->suit;
		current->face = swap->face; //replaces current's values with swap's
		current->suit = swap->suit;
		swap->face = temp->face; //replaces swap's values with old current's values stored in temp
		swap->suit = temp->suit;
		
		current = current->listp; //moves to next node
		free(temp); //free's temp's memory
	}

	return headp;
}

void printcard(card *headp) {
	char face = '0';
	char suit = '0';

	if (headp->face > 0) {
		if (headp->suit == 'c') {
			suit = 0x05; //hex for clubs
		}
		else if (headp->suit == 's') {
			suit = 0x06; //hex for spades
		}
		else if (headp->suit == 'h') {
			suit = 0x03; //hex for hearts
		}
		else if (headp->suit == 'd') {
			suit = 0x04; //hex for diamonds
		}

		if (headp->face == 100) { //only joker has face = 100, so prints joker card
			printf(" __________ \n");
			printf("|          |\n");
			printf("| Joker    |\n");
			printf("|          |\n");
			printf("|          |\n");
			printf("|          |\n");
			printf("|          |\n");
			printf("|    Joker |\n");
			printf("|__________|\n");
			
			//printf("Joker ");
		}
		else if (headp->face > 10 || headp->face == 1) { //if its a face card or an ace
			if (headp->face == 11) {
				face = 'J'; 
			}
			else if (headp->face == 12) {
				face = 'Q';
			}                                         //setting char face to whatever the stored int codes for
			else if (headp->face == 13) {
				face = 'K';
			}
			else if (headp->face == 1) {
				face = 'A';
			}

			printf(" __________ \n");
			printf("|          |\n");
			printf("| %c%c       |\n", face, suit);      //prints card w 2 characters: face char and suit
			printf("|          |\n");
			printf("|          |\n");
			printf("|          |\n");
			printf("|          |\n");
			printf("|       %c%c |\n", face, suit);
			printf("|__________|\n");

			//printf("%c%c ", face, suit);
		}
		else if (headp->face != 10) { //any number card other than 10
			printf(" __________ \n");
			printf("|          |\n");
			printf("| %d%c       |\n", headp->face, suit); //prints number and suit
			printf("|          |\n");
			printf("|          |\n");
			printf("|          |\n");
			printf("|          |\n");
			printf("|       %d%c |\n", headp->face, suit);
			printf("|__________|\n");

			//printf("%d%c ", headp->face, suit);
		}
		else if (headp->face == 10) { //only did this because 10 takes up 1 extra space compared to other nums, so 1 space was deleted from lines where num & suit are 
			printf(" __________ \n");
			printf("|          |\n");
			printf("| %d%c      |\n", 10, suit);
			printf("|          |\n");
			printf("|          |\n");
			printf("|          |\n");
			printf("|          |\n");
			printf("|      %d%c |\n", 10, suit);
			printf("|__________|\n");

			//printf("%d%c ", 10, suit);
		}
	}
}

card* DiscPairs(card *headp) {
	card *current = (card *)malloc(sizeof(card));
	card *bcurrent = (card *)malloc(sizeof(card));
	card *search = (card *)malloc(sizeof(card));
	card *bsearch = (card *)malloc(sizeof(card));

	bcurrent = headp; //before current
	current = headp->listp; //current starts after dummy head
	bsearch = current; //before search
	search = current->listp; //search starts after current, since we dont want one card to be seen as two

	while (current->listp != NULL) { //ends when end of list is reached
		while (search->listp != NULL) { //ends when search reaches end of list
			if (search->face == current->face) { //if the number is the same
				if (search->suit == 'c' || search->suit == 's') {
					if (current->suit == 'c' || current->suit == 's') {
						printf("\nRemove pair: \n");
						printcard(current);
						printcard(search);
						bsearch->listp = search->listp;
						bcurrent->listp = current->listp;
					}
				}                                                               //sorted by color: if color matches, then pair is printed, and then deleted from list
				else if (search->suit == 'h' || search->suit == 'd') {
					if (current->suit == 'h' || current->suit == 'd') {
						printf("\nRemove pair: \n");
						printcard(current);
						printcard(search);
						bsearch->listp = search->listp;
						bcurrent->listp = current->listp;
					}
				}
			}
			bsearch = bsearch->listp;
			search = search->listp;   //continues search
		}
		bcurrent = bcurrent->listp;
		current = current->listp;   //moves current and bcurrent to next node
		bsearch = current;
		search = current->listp;    //reinitializes search and bsearch
	}

	return headp;
}

int CardNum(card *headp) {
	int i = 0;
	card *current;

	current = headp->listp;
	while (current != NULL) {
		i++;
		current = current->listp;
	}

	return i;
}

void printdeck(card *headp) {
	card *current;
	
	current = headp;
	while (current != NULL) {
		printcard(current);          //prints deck
		current = current->listp;
	}

	printf("\n");
}

void pause() {
	printf("\n~~Press any key to continue~~\n\n");
	getch();
}

int main(void) {

	card *deck = NULL, *current = deck, *p1 = NULL, *p2 = NULL, *comp = NULL, *temp, *tail1 = NULL, *tail2 = NULL, *tail3 = NULL, *take, *btake;
	int i = 0, j = 0, k = 1, l = 0, loop = 0, tcard = 0, num = 0;
	char name1[20], name2[20], ans = 'y';
	srand((int)time(0));

	while (ans != 'q' || ans != 'Q') {
		deck = CreateDeck(deck);

		printf("Player 1, enter your name: ");
		scanf("%s", name1);
		printf("Player 2, enter your name: ");
		scanf("%s", name2);

		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n%s and %s, let's play Old Maid\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n", name1, name2);

		loop = 10 + (rand() % 10);
		for (i = 0; i < loop; i++) {
			deck = ShuffleCard(deck, 53); //shuffles deck at least 10 times (determined by "loop" above)
		}

		//printdeck(deck);
		//break;

		// Dealing deck
		current = deck;
		current = current->listp;

		temp = (card *)malloc(sizeof(card));  //
		temp->face = -1;                      //
		temp->suit = 'o';                     //
		p1 = temp;                            //
		tail1 = temp;                         //
		tail1->listp = NULL;                  //
		temp = (card *)malloc(sizeof(card));  //
		temp->face = -1;                      //
		temp->suit = 'o';                     //
		p2 = temp;                            // Adds 1st node, dummy head, to all three lists
		tail2 = temp;                         //
		tail2->listp = NULL;                  //
		temp = (card *)malloc(sizeof(card));  //
		temp->face = -1;                      //
		temp->suit = 'o';                     //
		comp = temp;                          //
		tail3 = temp;                         //
		tail3->listp = NULL;                  //


		while (current != NULL) {
			if (k == 1) {
				temp = (card *)malloc(sizeof(card)); //allocates needed memory to temp
				temp->face = current->face; //temp is assigned current's card number
				temp->suit = current->suit; //and suit
				if (p1 == NULL) { //only for first loop
					p1 = temp;
				}
				else {
					tail1->listp = temp; //adds temp to the end of the list
				}
				tail1 = temp;
				tail1->listp = NULL;
				k++; //adds one to k to distribute next card to next person
			}
			else if (k == 2) {
				temp = (card *)malloc(sizeof(card)); //allocates needed memory to temp
				temp->face = current->face; //temp is assigned current's card number
				temp->suit = current->suit; //and suit
				if (p2 == NULL) { //only for first loop
					p2 = temp;
				}
				else {
					tail2->listp = temp; //adds temp to the end of the list 
				}
				tail2 = temp;
				tail2->listp = NULL;
				k++; //adds one to k to distribute next card to next person
			}
			else if (k == 3) {
				temp = (card *)malloc(sizeof(card)); //allocates needed memory to temp
				temp->face = current->face; //temp is assigned current's card number
				temp->suit = current->suit; //and suit
				if (comp == NULL) { //only for first loop
					comp = temp;
				}
				else {
					tail3->listp = temp; //adds temp to the end of the list 
				}
				tail3 = temp;
				tail3->listp = NULL;
				k = 1; //goes back to giving p1 cards
			}
			current = current->listp; //moves to next node
		}

		printf("%s's hand has %d cards\n", name1, CardNum(p1));
		printdeck(p1); //prints p1's deck

		pause();

		printf("%s's hand has %d cards\n", name2, CardNum(p2));
		printdeck(p2); //prints p2's deck

		pause();

		printf("Dealer's hand: throw away pairs\n\n");
		comp = DiscPairs(comp);
		printf("\nI now have %d cards\n", CardNum(comp));  //discard comp's pairs and shows how many are left

		pause();

		printf("%s's hand: throw away pairs\n\n", name1);
		p1 = DiscPairs(p1);
		pause();
		printf("\n%s, this is your hand: \n", name1); //discards pairs and shows p1's hand
		printdeck(p1);

		pause();

		printf("%s's hand: throw away pairs\n\n", name2);
		p2 = DiscPairs(p2);
		pause();
		printf("\n%s, this is your hand: \n", name2); //discards pairs and shows p2's hand
		printdeck(p2);

		pause();

		if (CardNum(p1) > CardNum(p2) && CardNum(p1) > CardNum(comp)) { //if p1 has more cards than the others
			take = p2->listp; //will take cards from p2 (skips dummy head)
			printf("%s has more cards, you start\n", name1);
			l = 1; //just to identify
		}
		else if (CardNum(p2) > CardNum(p1) && CardNum(p2) > CardNum(comp)) { //if p2 has more cards than the others
			take = comp->listp; //will take cards from comp (skips dummy head)
			printf("%s has more cards, you start\n", name2);
			l = 2; //just to identify
		}
		else if (CardNum(comp) > CardNum(p1) && CardNum(comp) > CardNum(p2)) { //if comp has more cards than the others
			take = p1->listp; //will take cards from p1 (skips dummy head)
			printf("I have more cards, I start\n");
			l = 3; //just to identify
		}
		else if (CardNum(p1) == CardNum(p2)) { //if p1 has more cards than the others
			take = p2->listp; //will take cards from p2 (skips dummy head)
			printf("%s and %s have the same number of cards, %s starts\n", name1, name2, name1);
			l = 1; //just to identify
		}
		else if (CardNum(p2) == CardNum(comp)) { //if p2 has more cards than the others
			take = comp->listp; //will take cards from comp (skips dummy head)
			printf("%s and I have the same number of cards, %s starts\n", name2, name2);
			l = 2; //just to identify
		}
		else if (CardNum(comp) == CardNum(p1)) { //if comp has more cards than the others
			take = p1->listp; //will take cards from p1 (skips dummy head)
			printf("%s and I have the same number of cards, I start\n", name1);
			l = 3; //just to identify
		}

		pause();

		while (l != 0) {
			if (CardNum(p1) == 1) {
				if (p1->listp->face == 100) {
					printf("Sorry %s, you're the Joker.\n\n", name1);
					break;
				}
			}
			if (CardNum(p2) == 1) {
				if (p2->listp->face == 100) {
					printf("Sorry %s, you're the Joker.\n\n", name2);
					break;
				}
			}
			if (CardNum(p2) == 1) {
				if (comp->listp->face == 100) {
					printf("Congratulations, you both win, I'm the Joker.\n\n");
					break;
				}
			}

			
			if (l == 1) { //player 1 turn
				if (CardNum(p1) != 0 && CardNum(p2) != 0) {
					btake = p2;
					take = p2->listp;

					printf("%s has %d cards: \n", name2, CardNum(p2));
					for (i = 1; i <= CardNum(p2); i++) {
						printf(" %d ", i); //prints number of cards
					}
					printf("\nWhich one do you want to choose (1-%d)?: ", CardNum(p2));
					scanf("%d", &num);
					while (num <= 0 || num > CardNum(p2)) { //only lets code continue once user inputs valid number
						printf("I have ONLY %d cards", CardNum(p2));
						printf("\nWhich one do you want to choose (1-%d)?: ", CardNum(p2));
						scanf("%d", &num);
					}

					for (j = 0; j < num - 1; j++) { //cycles through deck until number selected by user
						btake = take;
						take = take->listp;
					}
					btake->listp = take->listp; //changes (node before taken card)'s listp to taken card's listp
					tail1->listp = take; //changes p1's last card to taken card
					tail1 = take; //changes tail to new card
					tail1->listp = NULL; //ends list after new card

					DiscPairs(p1);

					printf("\n%s, this is your (shuffled) hand: \n", name1); //prints p1's shuffled deck
					p1 = ShuffleCard(p1, CardNum(p1));
					printdeck(p1);
					
					printf("\n%s, this is your (shuffled) hand: \n", name2); //prints p2's shuffled deck
					p2 = ShuffleCard(p2, CardNum(p2));
					printdeck(p2);
				
					pause();
				}
				else if (CardNum(p1) != 0 && CardNum(p2) == 0 && CardNum(comp) != 0) {
					btake = comp;
					take = comp->listp;
					printf("%s, I have %d cards: \n", name1, CardNum(comp));
					for (i = 1; i <= CardNum(comp); i++) {
						printf(" %d ", i); //prints number of cards
					}
					printf("\nWhich one do you want to choose (1-%d)?: ", CardNum(comp));
					scanf("%d", &num);
					while (num <= 0 || num > CardNum(comp)) { //only lets code continue once user inputs valid number
						printf("I have ONLY %d cards", CardNum(comp));
						printf("\nWhich one do you want to choose (1-%d)?: ", CardNum(comp));
						scanf("%d", &num);
					}

					for (j = 0; j < num - 1; j++) { //cycles through deck until number selected by user
						btake = take;
						take = take->listp;
					}
					btake->listp = take->listp; //changes (node before taken card)'s listp to taken card's listp
					tail1->listp = take; //changes p2's last card to taken card
					tail1 = take; //changes tail to new card
					tail1->listp = NULL; //ends list after new card

					DiscPairs(p1);

					
					printf("\n%s, this is your (shuffled) hand: \n", name1); //prints p2's shuffled deck
					p1 = ShuffleCard(p1, CardNum(p1));
					printdeck(p1);

					pause();
				}

				l = 2;
			}
			else if (l == 2) { //player 2 turn
				if (CardNum(comp) != 0 && CardNum(p2) != 0) {
					btake = comp;
					take = comp->listp;
					printf("%s, I have %d cards: \n", name2, CardNum(comp));
					for (i = 1; i <= CardNum(comp); i++) {
						printf(" %d ", i); //prints number of cards
					}
					printf("\nWhich one do you want to choose (1-%d)?: ", CardNum(comp));
					scanf("%d", &num);
					while (num <= 0 || num > CardNum(comp)) { //only lets code continue once user inputs valid number
						printf("I have ONLY %d cards", CardNum(comp));
						printf("\nWhich one do you want to choose (1-%d)?: ", CardNum(comp));
						scanf("%d", &num);
					}

					for (j = 0; j < num - 1; j++) { //cycles through deck until number selected by user
						btake = take;
						take = take->listp;
					}
					btake->listp = take->listp; //changes (node before taken card)'s listp to taken card's listp
					tail2->listp = take; //changes p2's last card to taken card
					tail2 = take; //changes tail to new card
					tail2->listp = NULL; //ends list after new card

					DiscPairs(p2);

					
					printf("\n%s, this is your (shuffled) hand: \n", name2); //prints p2's shuffled deck
					p2 = ShuffleCard(p2, CardNum(p2));
					printdeck(p2);

					pause();
				}
				else if (CardNum(comp) == 0 && CardNum(p2) != 0 && CardNum(p1) != 0) {
					btake = p1;
					take = p1->listp;
					p1 = ShuffleCard(p1, CardNum(p1));

					printf("%s has %d cards: \n", name1, CardNum(p1));
					for (i = 1; i <= CardNum(p1); i++) {
						printf(" %d ", i); //prints number of cards
					}
					printf("\nWhich one do you want to choose (1-%d)?: ", CardNum(p1));
					scanf("%d", &num);
					while (num <= 0 || num > CardNum(p1)) { //only lets code continue once user inputs valid number
						printf("I have ONLY %d cards", CardNum(p1));
						printf("\nWhich one do you want to choose (1-%d)?: ", CardNum(p1));
						scanf("%d", &num);
					}

					for (j = 0; j < num - 1; j++) { //cycles through deck until number selected by user
						btake = take;
						take = take->listp;
					}
					btake->listp = take->listp; //changes (node before taken card)'s listp to taken card's listp
					tail2->listp = take; //changes p1's last card to taken card
					tail2 = take; //changes tail to new card
					tail2->listp = NULL; //ends list after new card

					DiscPairs(p2);

					printf("\n%s, this is your (shuffled) hand: \n", name2); //prints p2's shuffled deck
					p2 = ShuffleCard(p2, CardNum(p2));
					printdeck(p2);
					
					printf("\n%s, this is your (shuffled) hand: \n", name1); //prints p1's shuffled deck
					p1 = ShuffleCard(p1, CardNum(p1));
					printdeck(p1);					

					pause();
				}
				l = 3;
			}
			else if (l == 3) { //comp turn
				if (CardNum(comp) != 0 && CardNum(p1) != 0) {
					btake = p1;
					take = p1->listp;
					p1 = ShuffleCard(p1, CardNum(p1));

					tcard = rand() % CardNum(p1) + 1;
					printf("%s, I choose card #%d from you\n\n", name1, tcard);
					for (j = 0; j < tcard - 1; j++) { //cycles through deck until random num
						btake = take;
						take = take->listp;
					}

					btake->listp = take->listp; //changes (node before taken card)'s listp to taken card's listp
					tail3->listp = take; //changes comp's's last card to taken card
					tail3 = take; //changes tail to new card
					tail3->listp = NULL; //ends list after new card

					DiscPairs(comp);

					printf("I now have %d cards\n\n", CardNum(comp)); //prints p1's shuffled deck
					printf("\n%s, this is your hand: \n", name1);
					printdeck(p1);

					pause();
				}
				else if (CardNum(comp) != 0 && CardNum(p1) == 0 && CardNum(p2) != 0) {
					btake = p2;
					take = p2->listp;
					p2 = ShuffleCard(p2, CardNum(p2));

					tcard = rand() % CardNum(p2) + 1;
					printf("%s, I choose card #%d from you\n\n", name2, tcard);
					for (j = 0; j < tcard - 1; j++) { //cycles through deck until random num
						btake = take;
						take = take->listp;
					}

					btake->listp = take->listp; //changes (node before taken card)'s listp to taken card's listp
					tail3->listp = take; //changes comp's's last card to taken card
					tail3 = take; //changes tail to new card
					tail3->listp = NULL; //ends list after new card

					DiscPairs(comp);

					printf("I now have %d cards\n\n", CardNum(comp)); //prints p1's shuffled deck
					printf("\n%s, this is your hand: \n", name2);
					printdeck(p2);					

					pause();
				}
				l = 1;
			}
		}

		printf("Do you want to play again (q or Q to quit)?: ");
		scanf(" %c", &ans);
	}

	return 0;
}