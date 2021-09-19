//
//  UpTime.swift
//  Swift_5_Assign_2
//
//  Created by renpeng on 2021/4/22.
//

import Foundation

public class UpTime{
    // MARK: Variables declaration
    public var state : Int = -1
    public var step : Int = -1
    private var posThrs : Double, negThrs : Double, posPeakThrs : Double, negPeakThrs : Double = 0
    
    // MARK: Member functions
    init?(){
        state = 0
        step = 0
        posThrs = 0
        negThrs = 0
        posPeakThrs = 0
        negPeakThrs = 0
    }
    
    /*  UpTimes function. Implements the finite state machine from
        "UPTIME: Ubiquitous Pedestrian Tracking using Mobile Phones.”
        Transitions between various states depending on its input which
        is magnitude of accelerometer data minus 1. Default state is 0
        which is the start and state 6 is the final which is where the
        step counter is incremented.
    */
    public func UpTimes(mag: Double){
        posThrs = 0.02
        negThrs = -0.02
        posPeakThrs = 0.2
        negPeakThrs = -0.15
        
        switch(state){
        case 0:
            if mag < posThrs{
                state = 0
            }
            else if mag > posThrs{
                state = 1
            }
        case 1:
            if mag > posThrs && mag < posPeakThrs{
                state = 1
            }
            else if mag < posThrs {
                state = 4
            }
            else if mag > posPeakThrs{
                state = 2
            }
        case 2:
            if mag > posPeakThrs{
                state = 2
            }
            else if mag < negPeakThrs{
                state = 3
            }
        case 3:
            if mag < negPeakThrs{
                state = 3
            }
            else if mag > negPeakThrs{
                state = 5
            }
        case 4:
            if mag > posThrs{
                state = 1
            }
            else if mag < posThrs{
                state = 0
            }
        case 5:
            if mag < negPeakThrs{
                state = 3
            }
            else if mag > negPeakThrs && mag < negThrs{
                state = 5
            }
            else if mag > negThrs{
                state = 6
            }
        case 6:
            step += 1
            if mag < posThrs{
                state = 0
            }
            else if mag > posThrs{
                state = 1
            }
        default:
           state = 0
        }

    }
    
}
