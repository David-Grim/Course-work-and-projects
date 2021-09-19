//
//  AnotherViewController.swift
//  Swift_5_Assign_1
//
//  Created by David Grim on 4/18/21.
//

import UIKit

class AnotherViewController: UIViewController {

    //label at the top of the tab
    @IBOutlet weak var flip_history: UILabel!
    
    //text view for displaying the flip count and contents
    @IBOutlet weak var text_view: UITextView!
    
    
    /*  Load the text for the label at the top which is static and
        push the string text from the first view to this one and
        display it in the text view
    */
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidLoad()
        flip_history.text = "Flip History"
        let str = UserDefaults.standard.object(forKey: "string") as! String
        text_view.text.append(str)
    }
    
    /*  Function clears text when not in tab. this ensures the text
        doesn't duplicate since I'm appending to a string
    */
    override func viewWillDisappear(_ animated: Bool) {
        text_view.text = ""
    }
}
