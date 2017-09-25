# Da fare

| CHI | COSA            |
| --- | ---             |
| BV | Riempire stanze  |
| GB | Disegnare cose   |
| GB | Input            |
| VT | turno e dinamica |


+ Da aggiungere metodo per movimento di giocatore e mostri (eventuali parametri x,y,stanzacorrente dei personaggi)
+ Per la grafica: occorrono schermate di passaggio di livello e interfaccia per il venditore (si possono mettere in una sezione dello schermo, oppure semplicemente in una finestra riscritta da capo)
+ Ad ogni azione si fa corrispondere un diminuire dei punti azione, e ad ogni turno vengono resettati; da vedere se implementare il controllo dei punti direttamente nelle classi o nel metodo dei turni
+ Da aggiungere IA dei mostri nel metodo dei turni (si chiama ad esempio un metodo Muovi e un metodo Insegui a seconda che il giocatore sia in un quadrato 4x4 nei dintorni del mostro)
+ Da aggiungere condizioni di vittoria (metodo del turno)
+ Verificare funzionamento e correttezza dei vari metodi di giocatore, mostro, arma e venditore
+ Gestire la rimozione dal gioco dei forzieri dopo l'utilizzo e dei mostri dopo la morte
