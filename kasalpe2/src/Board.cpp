#include "Board.hpp"
#include <sstream>

Board::Board() {}

void Board::placeAntHill() // polozi anthill na mapu
{
    // implementace umístění mraveništ na desku
    for (const AntHill &anthill : AntsHill_onBoard)
    {
        int x = anthill.getPosition().getX();
        int y = anthill.getPosition().getY();
        board_for_print[y][x] = make_unique<AntHill>(anthill);
    }
}

void Board::placeObstacles(int x, int y) // polozi obstacles na mapu
{
    // Implementace umístění překážek na desku
    board_for_print[y][x] = make_unique<Obstacles>();
}

bool Board::checkplace(vector<AntHill> &AntsHill_onBoard, vector<Obstacles> &Obstacles_onBoard, int x, int y)
{
    for (const AntHill &anthill : AntsHill_onBoard)
    {
        if (!checkAroundPlace(anthill.getPosition().getX(), anthill.getPosition().getY(), x, y))
        {
            return false; // Duplicitní mraveniště
        }
    }
    return true; // Žádné duplicitní mraveniště
}

bool Board::checkAroundPlace(int x, int y, int new_x, int new_y) // kontroluje 3x3 bloky okolo mraveniste
{
    if (abs(new_x - x) <= 1 && abs(new_y - y) <= 1)
    {
        return false; // New coordinates are touching or overlapping the old coordinates
    }
    return true;
}

void Board::MakeMove(int id_from, int id_to, int choice) // choice 0 -> attack, 1 -> support, 2 -> bonus for id_from
{
    system("clear");
    if (choice == 0)
    {
        MakeMoveAttack(id_from, id_to);
    }
    else if (choice == 1)
    {
        MakeMoveSupport(id_from, id_to);
    }
    else if (choice == 2)
    {
        MakeMoveBonus(id_from);
    }
    else if (choice == 3)
    {
    }

    system("clear");
}

vector<Position> Board::FindWay(int id_from, int id_to)
{
    Position start = AntsHill_onBoard[id_from].getPosition();
    Position end = AntsHill_onBoard[id_to].getPosition();

    board_for_print[start.getY()][start.getX()]->setPassable(true);
    board_for_print[end.getY()][end.getX()]->setPassable(true);

    int numRows = board_for_print.size();
    int numCols = board_for_print[0].size();

    vector<vector<bool>> visited(numRows, vector<bool>(numCols, false));
    vector<vector<int>> distance(numRows, vector<int>(numCols, INT_MAX));
    vector<vector<Position>> predecessors(numRows, vector<Position>(numCols));

    queue<Position> q;

    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};

    q.push(start);
    visited[start.getY()][start.getX()] = true;
    distance[start.getY()][start.getX()] = 0;

    while (!q.empty())
    {
        Position current = q.front();
        q.pop();

        if (current == end)
        {
            // cout << "konec" << endl;
            break;
        }
        // cout << current.getX() << "||" << end.getX() <<"--" << current.getY() << "||" << end.getY() << endl;
        for (int i = 0; i < 4; i++)
        {
            int newRow = current.getY() + dr[i];
            int newCol = current.getX() + dc[i];

            if (isValidPosition(newRow, newCol) && !visited[newRow][newCol])
            {
                Position neighbor(newCol, newRow);
                q.push(neighbor);
                visited[newRow][newCol] = true;
                distance[newRow][newCol] = distance[current.getY()][current.getX()] + 1;
                predecessors[newRow][newCol] = current;
            }
            // cout << newRow <<  "||" << newCol << endl;
        }
    }

    vector<Position> path;

    if (distance[end.getY()][end.getX()] != INT_MAX)
    {
        Position current = end;
        while (current != start)
        {
            path.push_back(current);
            current = predecessors[current.getY()][current.getX()];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
    }

    board_for_print[start.getY()][start.getX()]->setPassable(false);
    board_for_print[end.getY()][end.getX()]->setPassable(false);
    return path;
}

bool Board::isValidPosition(int row, int col)
{
    int numRows = board_for_print.size();
    int numCols = board_for_print[0].size();
    return (row >= 0 && row < numRows && col >= 0 && col < numCols && board_for_print[row][col]->IsPassable());
}

int Board::MakeMoveBonus(int id_from)
{
    BonusMoreAnts effect1;
    effect1.setPrice(bonuses[0]);
    BonusStrongerAnts effect2;
    effect2.setPrice(bonuses[1]);
    BonusDefendAnts effect3;
    effect3.setPrice(bonuses[2]);
    BonusLevel effect4;
    effect4.setPrice(bonuses[3]);
    BonusFasterProduction effect5;
    effect5.setPrice(bonuses[4]);

    // Výběr bonusu
    if (AntsHill_onBoard[id_from].getlevel() >= tree_level)
    {
        cout << "Vyber bonus mas: " << money << "€" << endl;
        cout << "0. Jsem chudej a měl jsem vybrat jiny tah" << endl;
        cout << "1. Více mravenců (max. hodnota)"
             << "- " << effect1.getPrice() << "€" << endl;
        cout << "2. Silnější mravenci"
             << "- " << effect2.getPrice() << "€" << endl;
        cout << "3. Silnější obrana mravenců"
             << "- " << effect3.getPrice() << "€" << endl;
        cout << "4. Vyšší level mraveniště"
             << "- " << effect4.getPrice() << "€" << endl;
        cout << "5. Rychlejší produkce"
             << "- " << effect5.getPrice() << "€" << endl;
    }
    else
    {
        cout << "Vyber bonus mas: " << money << "€" << endl;
        cout << "0. Jsem Chudej a měl jsem vybrat jiny tah" << endl;
        cout << "1. Více mravenců (max. hodnota)"
             << "- " << effect1.getPrice() << "€" << endl;
        cout << "2. Silnější mravenci"
             << "- " << effect2.getPrice() << "€" << endl;
        cout << "3. Silnější obrana mravenců"
             << "- " << effect3.getPrice() << "€" << endl;
        cout << "4. Vyšší level mraveniště"
             << "- " << effect4.getPrice() << "€" << endl;
    }

    char choice;
    cin >> choice;
    if (std::cin.eof())
        return 0;
    // Zpracování výběru bonusu
    switch (choice)
    {

    case '0':
        break;
    case '1':

        if (money >= effect1.getPrice())
        {
            money = money - effect1.getPrice();
            effect1.applyEffect(AntsHill_onBoard[id_from]);
        }
        else
        {
            system("clear");
            cout << "Neplatná volba." << endl;
            MakeMoveBonus(id_from);
        }

        break;
    case '2':
        if (money >= effect2.getPrice())
        {
            money = money - effect2.getPrice();
            effect2.applyEffect(AntsHill_onBoard[id_from]);
        }
        else
        {
            system("clear");
            cout << "Neplatná volba." << endl;
            MakeMoveBonus(id_from);
        }

        break;
    case '3':
        if (money >= effect3.getPrice())
        {
            money = money - effect3.getPrice();
            effect3.applyEffect(AntsHill_onBoard[id_from]);
        }
        else
        {
            system("clear");
            cout << "Neplatná volba." << endl;
            MakeMoveBonus(id_from);
        }
        break;
    case '4':
        if (money >= effect4.getPrice())
        {
            money = money - effect4.getPrice();
            effect4.applyEffect(AntsHill_onBoard[id_from]);
        }
        else
        {
            system("clear");
            cout << "Neplatná volba." << endl;
            MakeMoveBonus(id_from);
        }
        break;
    case '5':
        if (AntsHill_onBoard[id_from].getlevel() >= tree_level && money >= effect5.getPrice())
        {
            money = money - effect5.getPrice();
            effect5.applyEffect(AntsHill_onBoard[id_from]);
        }
        else
        {
            system("clear");
            cout << "Neplatná volba." << endl;
            MakeMoveBonus(id_from);
        }
        break;
    default:
        system("clear");
        cout << "Neplatná volba." << endl;
        MakeMoveBonus(id_from);
    }
    return 1;
}

void Board::MakeMoveSupport(int id_from, int id_to)
{
    if (id_from != id_to)
    {
        /* code */

        vector<Position> way;
        way = FindWay(id_from, id_to);

        /* code */

        Ant Ants(AntsHill_onBoard[id_from]); // mravenci dle mraveniště

        // Odebrání prvního prvku // start
        if (!way.empty())
        {
            way.erase(way.begin());
        }
        // Odebrání posledního prvku //konec
        if (!way.empty())
        {
            way.pop_back();
        }
        for (auto it = way.begin(); it != way.end(); ++it)
        {
            system("clear");
            const auto &test = *it;

            if (it == way.begin())
            {
                board_for_print[test.getY()][test.getX()] = make_unique<Ant>(Ants);
            }
            else if (it == way.end())
            {
                board_for_print[test.getY()][test.getX()] = make_unique<EmptySpace>();
            }
            else
            {
                const auto &previous = *std::prev(it);
                board_for_print[previous.getY()][previous.getX()] = make_unique<EmptySpace>();
                board_for_print[test.getY()][test.getX()] = make_unique<Ant>(Ants);
            }
            printBoard();
            this_thread::sleep_for(std::chrono::milliseconds(50)); // Zpoždění 50 milisekund
        }
        board_for_print[way.back().getY()][way.back().getX()] = make_unique<EmptySpace>();
        system("clear");
        printBoard();
        AntsHill_onBoard[id_to].support(AntsHill_onBoard[id_from]);
    }
}

void Board::MakeMoveAttack(int id_from, int id_to)
{
    vector<Position> way;
    way = FindWay(id_from, id_to);

    Ant Ants(AntsHill_onBoard[id_from]); // mravenci dle mraveniště

    // Odebrání prvního prvku // start
    if (!way.empty())
    {
        way.erase(way.begin());
    }
    // Odebrání posledního prvku //konec
    if (!way.empty())
    {
        way.pop_back();
    }
    for (auto it = way.begin(); it != way.end(); ++it)
    {
        system("clear");
        const auto &test = *it;

        if (it == way.begin())
        {
            board_for_print[test.getY()][test.getX()] = make_unique<Ant>(Ants);
        }
        else if (it == way.end())
        {
            board_for_print[test.getY()][test.getX()] = make_unique<EmptySpace>();
        }
        else
        {
            const auto &previous = *std::prev(it);
            board_for_print[previous.getY()][previous.getX()] = make_unique<EmptySpace>();
            board_for_print[test.getY()][test.getX()] = make_unique<Ant>(Ants);
        }
        printBoard();
        this_thread::sleep_for(std::chrono::milliseconds(50)); // Zpoždění 50 milisekund
    }
    board_for_print[way.back().getY()][way.back().getX()] = make_unique<EmptySpace>();
    if (AntsHill_onBoard[id_to].Attack(AntsHill_onBoard[id_from]))
    {
        board_for_print[AntsHill_onBoard[id_to].getPosition().getY()][AntsHill_onBoard[id_to].getPosition().getX()] = make_unique<AntHill>(AntsHill_onBoard[id_to]);
    }

    system("clear");
    printBoard();
}

void Board::BoardForPrintMake(int y_board, int x_board) // vytvoří 2d pole pro tisk mapy
{
    board_for_print.resize(x_board);
    for (int row = 0; row < x_board; row++)
    {
        board_for_print[row].resize(y_board);
        for (int col = 0; col < y_board; col++)
        {
            if (row == 0 || row == x_board - 1 || col == 0 || col == y_board - 1)
            {
                board_for_print[row][col] = std::make_unique<Obstacles>();
            }
            else
            {
                board_for_print[row][col] = std::make_unique<EmptySpace>();
            }
        }
    }
}

void Board::AnalyseGameBot()
// jednou za 3 kola neudela nic,... abych ho porazil
// pokud má více jak 40€ koupí jednou za 2 kola bonus na max_ants
// pokud má nejmenší utocnou silu mravencu, zvetsuje sílu
// pokud již nema nejmenší utocnou silu zautočí na nejbližší mraveniste
// zaroven se nevykonaji 2 stejny akce za sebou
{
    int id_from_pc = -1;
    int id_to_pc = -1;
    BonusMoreAnts effect1;
    effect1.setPrice(bonuses[0]);
    BonusStrongerAnts effect2;
    effect2.setPrice(bonuses[1]);
    pocitac.max_utok = 0;
    pocitac.money = pocitac.money + 10;
    pocitac.pauza_kolo = pocitac.pauza_kolo + 1;
    if (pocitac.pauza_kolo <= 3) // neni pauza kolo
    {
        if (pocitac.money > 40 && !pocitac.nakup) // jeden ze 2 kol probíhá nákup ale musí mít víc jak 40€
        {
            for (auto &anthill : AntsHill_onBoard) // prvnímu mravenisti -> tomu hlavnímu se koupí bonus na vetší počet mravencu
            {
                if (anthill.getOwner() == 2 && pocitac.money >= effect1.getPrice())
                {
                    pocitac.money = pocitac.money - effect1.getPrice();
                    effect1.applyEffect(anthill);
                    pocitac.nakup = true;
                    break;
                }
            }
        }
        else
        { // zjisti jestli má větší sílu než nějaké mraveniště pokud ano tak zautoci na to slabší mraveniště mraveniste pokud ne tak zvysi silu mravencu
            pocitac.nakup = false;
            pocitac.utok = false;
            system("clear");
            for (auto &anthill : AntsHill_onBoard)
            {
                // nejsilnejsi utok pocitace
                if (anthill.getOwner() == 2)
                {
                    int attack_ant = anthill.getNumberOfAnts() * anthill.getlevel() * anthill.getAttack();
                    if (attack_ant > pocitac.max_utok)
                    {
                        pocitac.max_utok = attack_ant;
                        id_from_pc = anthill.getId();
                    }
                }
            }

            // jestli nekoho porazí tak na něj zautočí
            for (auto &anthill : AntsHill_onBoard)
            {
                // kouknuti jestli je nekdo slabsi
                if (anthill.getOwner() != 2)
                {
                    int deffend_ant = anthill.getNumberOfAnts() * anthill.getlevel() * anthill.getDefend();
                    if (deffend_ant < pocitac.max_utok)
                    {
                        id_to_pc = anthill.getId();
                        MakeMoveAttack(id_from_pc, id_to_pc);
                        pocitac.utok = true;
                        system("clear");
                        break;
                    }
                }
            }
            if (!pocitac.utok)
            {
                for (auto &anthill : AntsHill_onBoard)
                {
                    // nejsilnejsi utok pocitace
                    if (anthill.getOwner() == 2)
                    {
                        id_from_pc = anthill.getId();
                        effect2.applyEffect(AntsHill_onBoard[id_from_pc]);
                        break;
                    }
                }
            }
        }
    }
    else // nevykoná se nic
    {
        pocitac.pauza_kolo = 0;
    }
}

void Board::printAnthillOwner(int owner) // tiskne mraveniste podle majitele
{                                        // tiskne id mravenist dle ownera
    cout << "\n";
    for (const AntHill &anthill : AntsHill_onBoard)
    {
        if (anthill.getOwner() == owner)
        {
            cout << "Id:" << anthill.getId() << " lvl: " << anthill.getlevel() << " -> " << anthill.getNumberOfAnts() << " || " << anthill.getMaxNumberOfAnts() << " A: " << anthill.getAttack() << " D: " << anthill.getDefend() << endl;
        }
    }
}

char Board::printChoiceOfMove() // tiskne možnosti co udelat utok -> obrana
{
    char choice = 0;
    cout << "Vyber moznosti je zavazny" << endl;
    cout << "1: Útok" << endl;
    cout << "2: Podpora" << endl;
    cout << "3: Bonus" << endl;
    cout << "4: Nic" << endl;
    cout << "5: Uložit" << endl;
    cout << "6: UKončit" << endl;
    cin >> choice;
    system("clear");
    printBoard();
    return choice;
}

int Board::printChoiceAnthillFrom() // z jakeho mraveniste se utoci
{
    int id;
    for (const AntHill &anthill : AntsHill_onBoard)
    {
        if (anthill.getOwner() == 1)
        {
            cout << anthill.getId() << " -> " << anthill.getNumberOfAnts() << endl;
        }
    }
    cin >> id;
    if (std::cin.eof())
    {
        return 0;
    }
    if (cin.fail())
    {
        cin.clear();                                         // Vynulovat příznaky chyby u cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorovat zbylé znaky ve vstupním proudu až do konce řádku
    }
    else
    {
        for (const AntHill &anthill : AntsHill_onBoard)
        {
            if (anthill.getOwner() == 1)
            {
                if (anthill.getId() == id)
                {
                    return id;
                }
            }
        }
    }
    system("clear");
    printBoard();
    cout << "Zadej svoje mraveniště odkud se vykoná akce" << endl;
    return printChoiceAnthillFrom();
}

// public
bool Board::loadMap(string name_of_map) // nacteni mapy -> vybrani velikost hriste a pozice barier + pozice mravenistw
{
    bool anthils_is_set = false;

    map = name_of_map;
    x_board = 0;
    y_board = 0;
    string Maps = "examples/";
    string File_Name = Maps + name_of_map; // cesta ke složce + nazev vybrane mapy
    ifstream file(File_Name);              // otevreni souboru
    if (file.is_open())
    {
        string line;
        bool allValuesFound = true;

        getline(file, line);
        size_t xPos = line.find("x: ");
        if (xPos != string::npos)
        {
            Board::x_board = stoi(line.substr(xPos + 3));
        }
        else
        {
            allValuesFound = false;
        }

        getline(file, line);
        size_t yPos = line.find("y: ");
        if (yPos != string::npos)
        {
            Board::y_board = stoi(line.substr(yPos + 3));
        }
        else
        {
            allValuesFound = false;
        }

        getline(file, line);
        size_t treePos = line.find("t: ");
        if (treePos != string::npos)
        {
            Board::tree_level = stoi(line.substr(treePos + 3));
        }
        else
        {
            allValuesFound = false;
        }

        BoardForPrintMake(x_board, y_board);

        for (int i = 0; i < 5; i++)
        {
            getline(file, line);
            size_t bonusPos = line.find("b: ");
            if (bonusPos != string::npos)
            {
                Board::bonuses.push_back(stoi(line.substr(bonusPos + 3)));
            }
            else
            {
                allValuesFound = false;
            }
        }

        if (!allValuesFound)
        {
            return false;
        }

        while (getline(file, line)) // prochazi vsechny radky
        {
            if (line.find("anthills:") != string::npos) // našlo to anthills
            {

                int id = 0; // Inkrementace ID před cyklem while
                int x = 0;
                int y = 0;
                while (getline(file, line) && line.find("-") != string::npos) // najde to pomlcku -> další mraveniste
                {

                    getline(file, line); // Načtení řádku s "x:"
                    try
                    {
                        x = stoi(line.substr(line.find(":") + 1));
                    }
                    catch (const invalid_argument &e)
                    {
                        continue;
                    }

                    getline(file, line); // Načtení řádku s "y:"
                    try
                    {
                        y = stoi(line.substr(line.find(":") + 1));
                    }
                    catch (const invalid_argument &e)
                    {
                        continue;
                    }

                    if (((x < x_board - 1 && x > 1) && (y < y_board - 1 && y > 1)) && checkplace(AntsHill_onBoard, Obstacles_onBoard, x, y))
                    {
                        AntHill new_Anthill(id, x, y);
                        AntsHill_onBoard.push_back(new_Anthill); // dám mraveniste do vektoru
                        id++;                                    // Inkrementace ID pro další mraveniště
                    }
                }
                anthils_is_set = true;
            }
            else if (line.find("obstacles:") != string::npos && line.substr(0, 10) == "obstacles:")
            {
                while (getline(file, line) && !line.empty())
                {

                    // Rozdělení řádku podle čárky na souřadnice x a y
                    size_t commaPos = line.find(",");
                    if (commaPos != string::npos)
                    {
                        int x = stoi(line.substr(0, commaPos));
                        int y = stoi(line.substr(commaPos + 1));

                        // Přidání překážky do vektoru
                        if (((x < x_board - 1 && x > 1) && (y < y_board - 1 && y > 1)) && checkplace(AntsHill_onBoard, Obstacles_onBoard, x, y))
                        {
                            placeObstacles(x, y);
                        }
                    }
                }
            }
        }
        file.close();
        system("clear");
    }
    else
    {
        cout << "Nepodařilo se otevřít soubor." << endl;
        return false;
    }

    if (x_board == 0 || y_board == 0) // kontrola že je zadane x a y
    {
        cout << "Spatný konfiguracni soubor nektere hodnoty byly dodany automaticky\n"
             << endl;
        x_board = 100;
        y_board = 25;
    }
    if (!anthils_is_set)
    {
        return false;
    }

    return true;
}

bool Board::checkWin() // kontroluje jestli někdo nevyhral
{
    bool tmp = false;
    tmp = std::all_of(AntsHill_onBoard.begin(), AntsHill_onBoard.end(), [](const AntHill &anthill)
                      { return anthill.getOwner() == 1; });

    if (tmp == true)
    {
        cout << "Vyhrál jsi" << endl;
        return true;
    }
    else
    {
        for (auto &anthill : AntsHill_onBoard)
        {
            if (anthill.getOwner() == 1)
            {
                return false;
            }
        }
    }

    cout << "Prohrál jsi" << endl;
    return true;
}

void Board::status() // tiskne jak na tom jsou mraveniste //zaroven vykonava ukony napr pricitani penez pricteni mravencu do mapy,...
{                    // tisk aktuálních mravenist
    if (money < 0)
    {
        money = 0;
    }
    for (auto &anthill : AntsHill_onBoard)
    {
        anthill.ProduceAnts();
    }

    money = money + 10;
    // // projiti mravenist a pricteni dle jejich produkce až do max_hodnoty

    cout << "Mraveniště hráče: ";
    printAnthillOwner(1);
    cout << endl;

    // // cout << "Mraveniště neobsazené: ";
    // // printAnthillOwner(0);
    // // cout << endl;

    cout << "Mraveniště počítače: ";
    printAnthillOwner(2);
    cout << "\nPenize: " << money << "€\n"
         << endl;
}

void Board::printBoard() // tiskne mapu
{
    for (long unsigned int row = 0; row < board_for_print.size(); row++)
    {
        for (long unsigned int col = 0; col < board_for_print[row].size(); col++)
        {
            board_for_print[row][col]->print();
        }
        cout << endl;
    }
}

int Board::printMove() // zpracovava tisk a vyber ukonu
{                      // tiskne možné tahy
    char choice = printChoiceOfMove();
    int id_from = -1;
    int id_to = -1;
    switch (choice)
    {
    case '1': // Kód pro provedení akce Attack
        cout << "Útok z mraveniště" << endl;
        id_from = printChoiceAnthillFrom(); // otazka odkud se zautoci
        if (std::cin.eof())
            return false;
        system("clear");
        printBoard();
        cout << "Kam chceš zaútočit" << endl;
        id_to = AntsHill_onBoard[id_from].printAttackTo(AntsHill_onBoard); // kam se zautoci
        if (std::cin.eof())
            return false;
        MakeMove(id_from, id_to, 0);
        AnalyseGameBot();

        break;
    case '2': // Kód pro provedení akce Support
        cout << "Podpora z mraveniště" << endl;
        id_from = printChoiceAnthillFrom(); // otazka odkud se podpori
        if (std::cin.eof())
            return false;
        system("clear");
        printBoard();
        cout << "Kam chceš Podporit" << endl;
        id_to = AntsHill_onBoard[id_from].printSupportTo(AntsHill_onBoard); // kam se podpori
        MakeMove(id_from, id_to, 1);
        AnalyseGameBot();

        break;
    case '3': // Kód pro provedení akce Bonus
        cout << "Kam chces umistit bonus" << endl;
        id_from = printChoiceAnthillFrom();
        if (std::cin.eof())
            return false;
        MakeMove(id_from, -1, 2);
        if (std::cin.eof())
            return false;
        AnalyseGameBot();

        break;
    case '4': // Kód pro provedení akce Nic
        system("clear");
        MakeMove(-1, -1, 3);
        AnalyseGameBot();

        break;
    case '5': // Kód pro provedení akce Uložit
        system("clear");
        return 2;
        break;
    case '6': // Kód pro provedení akce Ukončit
        system("clear");
        return 0;
        break;
    default:
        if (std::cin.eof())
        {
            return 0;
        }
        cout << "Neplatná volba -> zvol něco jiného" << endl;

        printMove();
    }

    return 1;
}

vector<AntHill> Board::getAntHill_on_board()
{
    return AntsHill_onBoard;
}

bool Board::setAntHill_on_board(vector<AntHill> &new_AntsHill)
{ // vrati false pokud se nepovede nacist novy vector anthill
    int ctr = 0;
    if (new_AntsHill.size() != AntsHill_onBoard.size())
    {
        return false;
    }
    for (auto &anthill : AntsHill_onBoard)
    {

        anthill.loadnewAntHills(new_AntsHill[ctr].getId(), new_AntsHill[ctr].getlevel(), new_AntsHill[ctr].getNumberOfAnts(), new_AntsHill[ctr].getMaxNumberOfAnts(), new_AntsHill[ctr].getOwner(), new_AntsHill[ctr].getAttack(), new_AntsHill[ctr].getDefend());
        ctr++;
    }

    return true;
}