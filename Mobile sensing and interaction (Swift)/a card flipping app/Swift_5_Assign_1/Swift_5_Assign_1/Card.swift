//
//  Card.swift
//  Swift_5_Assign_1
//
//  Created by renpeng on 2021/4/13.
//

import Foundation

public class Card{
    // Card's member variables
    public var contents: String = ""
    public var chosen: Bool = false
    private var rank: Int = 0
    private var suit: String = ""
    private var validRanks = ["A","2","3","4","5","6","7","8","9","10","J","K","Q"]
    private var validSuits = ["♦️","♥️","♠️","♣️"]
    init(){
        self.randomCard()
        chosen = false
    }
    func randomCard(){
        contents = validRanks.randomElement()! + validSuits.randomElement()!
    }
    
}
