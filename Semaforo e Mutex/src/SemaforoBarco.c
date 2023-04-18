#define N 4
typedef int semaphore;
semaphore mutex = 1; //Acesso a região crítica
semaphore empty = N; //Controla os lugares vazios no barco
semaphore full = 0; //Conta os lugares preenchidos no barco

int contadorHacker = 0;
int contadorServo = 0;

void hacker(void){

    while(true){
        
        if(full == 3){
            if(contadorServo == 1 || contadorServo == 3){
                sleep(); //NÃO FAZ NADA. ÚNICA POSSIBILIDADE É 1 PAR DE CADA!!!
            }
            else {
                down(&empty); //Diminui os lugares vazios no barco
                down(&mutex); //Entra na região crítica
                board(); //Thread embarcou no barco
                rowBoat(); //O barco vai remar. Na função rowBoat, todos os contadores voltam para seu estado inicial
                up(&mutex); //Sai da região crítica
                up(&full); //Incrementa os lugares ocupados
                wakeUp(servo); //Acorda servo, caso ele esteja no sleep
            }
        }
        else{
            down(&empty); //Diminui os lugares vazios no barco
            down(&mutex); //Entra na região crítica
            board(); //Thread embarcou no barco
            contadorHacker++; //Incrementa a quantidade de hackers no barco
            up(&mutex); //Sai da região crítica
            up(&full); //Incrementa os lugares ocupados

        }
    }
}


void servo(void){

    while(true){

        if(full == 3){
            if(contadorHacker == 1 || contadorHacker == 3){
                sleep()//NÃO FAZ NADA. ÚNICA POSSIBILIDADE É 1 PAR DE CADA!!!
            }
            else {
                down(&empty); //Diminui os lugares vazios no barco
                down(&mutex); //Entra na região crítica
                board(); //Thread embarcou no barco
                rowBoat(); //O barco vai remar. Na função rowBoat, todos os contadores voltam para seu estado inicial
                up(&mutex); //Sai da região crítica
                up(&full); //Incrementa os lugares ocupados
                wakeUp(hacker); //acorda hacker, caso ele esteja no sleep
            }
        }
        else {
            down(&empty); //Diminui os lugares vazios no barco
            down(&mutex); //Entra na região crítica
            board(); //Thread embarcou no barco
            contadorServo++; //Incrementa a quantidade de servos no barco
            up(&mutex); //Sai da região crítica
            up(&full); //Incrementa os lugares ocupados
        }
    }
}

void rowBoat(){

    //Barco rema e depois as variáveis de controle voltam para o valor original;

    semaphore mutex = 1; //Acesso a região crítica
    semaphore empty = N; //Controla os lugares vazios no barco
    semaphore full = 0; //Conta os lugares preenchidos no barco

    int contadorHacker = 0;
    int contadorServo = 0;
}









void producer(void)
{
    int item;

    while(true){
        item = produce_item();
        down(&empty);
        down(&mutex);
        insert_item(item);
        up(&mutex);
        up(&full);
    }
}

void consumer(void){
    int item;

    while(true){
       down(&full);
       down(&mutex);
       item = remove_item();
       up(&mutex);
       up(&empty);
       consume_item(item);
    }
}