//
//  ViewController.swift
//  Swift_5_Assign_1
//
//  Created by renpeng on 2021/4/13.
//

import UIKit

class ViewController: UIViewController {
    @IBOutlet weak var num_flips: UILabel!//--for displaying number of flips
    @IBOutlet weak var contents: UILabel!//--for displaying card.contents
    
    var str = "" //--for appending the cards contents and flip count
    var check = true //--bool for checking if text should be appended
    let card = Card()//--card object
    var numFlips = 0 //--flip counter
    
    /*   Function for initial load of the view. Flip count is initially 0
         and the cards contents shouldnt be shown since the initial card
         is on its back
    */
    override func viewDidLoad() {
        super.viewDidLoad()
        contents.text = ""
        num_flips.text = "Flip Count: " + String(numFlips)
        numFlips += 1
    }
    
    /*   Function to set what happens after every push of the UI button on
         the card tab. Sets what to do when the card is chosen or not
         chosen. Appends the cards contents to a string for and stores it
         for the history tab
    */
    @IBAction func push_button(_ sender: UIButton) {
        if check{
            UserDefaults.standard.set(card.chosen, forKey: "is_card_chosen")
            str.insert(contentsOf: String(numFlips) + " : " + card.contents + "\n", at: str.startIndex)
            
        }
        
        UserDefaults.standard.set(str, forKey: "string")
        card.chosen = !card.chosen
        num_flips.text = "Flip Count: " + String(numFlips)
        
        if card.chosen{
            contents.text = card.contents
            let backgroundImg = UIImage(named: "cardfront")!
            sender.setBackgroundImage(backgroundImg, for: .normal)
            check = false
        }
        else{
            contents.text = ""
            numFlips += 1
            card.randomCard()
            let backgroundImg = UIImage(named: "cardback")!
            sender.setBackgroundImage(backgroundImg, for: .normal)
            check = true
        }
    }
}

