#include <iostream>
#include <fstream>

struct node{ //node to hold start and end positions of strings that are stored in the char array(string pool)

  int word_start = 0; //string start position
  int word_end = 0; //string end position
  int count = 0; //string repitition count

  bool operator < (const node&); //operator overloading for struct, to make sorting easier
  bool operator > (const node&);
};


void finite_state_machine(std::string); //prototype functions
void insertion_sort();

char word_array[500000] = {}; //char array(string pool)
node node_array[50000] = {}; //struct object that acts to form words from the string pool
int counter = 0;
int node_counter = 0; //count how many unique words there are
int word_counter = 0; //count how many words in total
int word_total_length = 0; //count how many characters in total

int main(){

  std::string file_name;
  std::string file_word;

  std::cout << "Enter a file name and extension to read: " << std::endl;
  std::cin >> file_name; //input a file name

  std::fstream file;
  file.open(file_name); //open input file name

  if(!file){ //if file does not exist, send error message and exit program

    std::cerr << "The file failed to open. Exiting program..." << std::endl;
    return -1;

  } else { //else display success opening file message

    std::cout << file_name << " successfully opened..." << std::endl;

  }

  while(file >> file_word){ //while there are strings in the input text file

    if(file.bad()){ //if data input/output error occurs, send error message and exit program

      std::cerr << "File input/output error occured. Exiting program..." << std::endl;
      return -2;

    } else { //else run finite_state_machine function

      finite_state_machine(file_word); //takes words and stores into string pool

    }
  }

  word_array[word_total_length + 1] = '\0'; //null character to mark the end of the char array

  std::cout << "\nWord Total: " << word_counter << std::endl;
  std::cout << "Character Total: " << word_total_length << std::endl;
  std::cout << "Node Total: " << node_counter << std::endl;

  // insertion_sort(); //sorting to sort by count decreasing and alphabetically

  insertion_sort();

  std::string sorted_word; //store string temporarily for output later

  std::cout << "\n****************First Ten Words****************" << std::endl;

  for(int r = 0; r < 10; r++){ //first ten words to print out

    sorted_word = "";

    for(int s = node_array[r].word_start; s <= node_array[r].word_end; s++){ //from start position to end position, adds chars to temporary string, from string pool, for output
      sorted_word += word_array[s];
    }

    std::cout << "\nIndex: " << r << " Word Start: " << node_array[r].word_start << " Word End: " << node_array[r].word_end << " Count: " << node_array[r].count << "\n";
    std::cout << "Word: " << sorted_word << std::endl;

  }

  std::cout << "\n****************Last Ten Words****************" << std::endl;

  for(int r = (node_counter - 10); r < node_counter; r++){//last ten words to print out

    sorted_word = "";

    for(int s = node_array[r].word_start; s <= node_array[r].word_end; s++){//from start position to end position, adds chars to temporary string, from string pool, for output
      sorted_word += word_array[s];
    }

    std::cout << "\nIndex: " << r << " Word Start: " << node_array[r].word_start << " Word End: " << node_array[r].word_end << " Count: " << node_array[r].count << "\n";
    std::cout << "Word: " << sorted_word << std::endl;

  }



  return 0;
}


void finite_state_machine(std::string word){//finite state machine for string pool storage

  bool inword = true; //bool to show whether char in string is valid for storage in string pool
  bool repeat_word = false; //bool to show if a word is already stored in struct array
  int word_length_counter = 0; //count how long each string is
  node tree_node; //struct object for storing start and end positions, and counts
  std::string new_word = ""; //used to store processed string that is valid
  std::string word_compare; //used to compare struct array words with current string being passed


  for (int i = 0; i < word.length(); i++){

    if(word[i] == '\0'){//if char is a white space, inword = false

      inword = false;

    } else if (isalpha(word[i]) == 0){ //if char is not alphabetical, inword = false

      inword = false;

    } else if (isalpha(word[i]) != 0){ //if char is alphabetical, inword = true

      inword = true;

      word_array[word_total_length] = tolower(word[i]); //add to char array (string pool) lowercase of each valid char of the current string

      new_word += tolower(word[i]); //add to temporary string storage the lowercase of each valid char

      word_total_length++; //total count of characters increase
      word_length_counter++; //current count of characters in string
    }

  }

  if(node_counter > 0){ //if there is more than zero elements in the node array
    for(int j = 0; j < node_counter; j++){ //for index less than elements in node array

      word_compare = ""; //reset string for temporary storage each iteration

      for(int k = node_array[j].word_start; k < (node_array[j].word_end + 1); k++){ //from start position to end position, adds chars to temporary string, from string pool, for comparison

        word_compare += word_array[k];

      }

      if(new_word == word_compare){ //if the current valid string is equal to an element in the node array, set repeat_word to true, count for that element in node array increase, break

        node_array[j].count++;
        repeat_word = true;
        break;
      }

    }
  }

  if(repeat_word == false){ //if current processed string is not a repeat, add to node array, increase element count

    tree_node.word_start = (word_total_length - word_length_counter); //start position of each word is the total characters - characters in the processed string
    tree_node.word_end = (word_total_length - 1); // end position of each word is total characters - 1
    tree_node.count += 1; //count for that word increase

    node_array[node_counter] = tree_node;
    node_counter++; //element count in node array
  }


  word_counter++; //total word count
}

bool node::operator < (const node &node_one){ //operator overload for comparisons of objects when sorting

  if(count < node_one.count){ //if the count of the element left of operator is less than count of right, left node is less than right node

    return true;

  }

  if (count == node_one.count) { //if the node counts are equal

    if(word_array[word_start] == word_array[node_one.word_start]){ //if first char of both nodes are the same

      if(word_array[word_start + 1] > word_array[node_one.word_start + 1]){ //go to second char of each node
        return true; //return true if alphabetical
      }

    }

    if(word_array[word_start] > word_array[node_one.word_start]){ //return true if alphabetical
      return true;
    }
  }


  return false; //return left node not less than right node
}

bool node::operator > (const node &node_one){ //operator overload for comparisons of objects when sorting

  if(count > node_one.count){ //if the count of the element left of operator is higher than count of right, left node is higher than right node

    return true;

  }

  if (count == node_one.count) { //if the node counts are equal


    if(word_array[word_start] == word_array[node_one.word_start]){ //if first char of both nodes are the same

      if(word_array[word_start + 1] < word_array[node_one.word_start + 1]){ //go to second char of each node
        return true; //return true if alphabetical
      }

    }

    if(word_array[word_start] < word_array[node_one.word_start]){ //return true if alphabetical
      return true;
    }

  }


  return false; //return left node not higher than right node
}


void insertion_sort(){ //insertion sort to sort nodes by decreasing count and if count equal, then alphabetically

  node temp; //temporary node
  int position = 0;

  for(int z = 1; z < word_counter + 1; z++){ //start from second element in array, sorting is based on highest count and alphabetically if count equal

    temp = node_array[z]; //store node at position z in temporary node
    position = z - 1; //index of previous element

    while(position > -1 && node_array[position] < temp){ //while previous element index >=0 AND previous element of array is less than next element

      node_array[position + 1] = node_array[position]; //current element equals previous element in array
      position = position - 1; //position is now the next previous element index

    } //repeat process

    node_array[position + 1] = temp; //next element is equal to current element held in temporary node
  }

}
