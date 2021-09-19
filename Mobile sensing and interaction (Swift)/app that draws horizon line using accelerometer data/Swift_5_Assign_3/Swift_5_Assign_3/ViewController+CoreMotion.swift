//
//  ViewController+CoreMotion.swift
//  Swift_5_Assign_3
//
//  Created by renpeng on 2021/5/5.
//

import Foundation
import CoreMotion
import UIKit

extension ViewController{
    
    
    /* Start reporting CoreMotion updates */
    func startCoreMotion(){
        // Your code here to start any sensor updates
        // ...
        if sensorDevice == .DEVICE_MOTION{
        if motion.isDeviceMotionAvailable{
            motion.deviceMotionUpdateInterval = 1.0/60.0
            motion.startDeviceMotionUpdates(using: .xArbitraryZVertical, to: OperationQueue.current!, withHandler: {
                (data,error) in
                guard let gravityInDeviceRefFrame = data?.gravity, error == nil else {
                    print(error?.localizedDescription ?? "Nil")
                    return
                }
                
                let XC = gravityInDeviceRefFrame.x
                let YC = -(gravityInDeviceRefFrame.y)
                let ZC = -(gravityInDeviceRefFrame.z)
                
                self.A = XC
                self.B = YC
                self.C = -(XC*(720/2)) - (YC*(1280/2)) + ZC*480
                print("XB: \(gravityInDeviceRefFrame.x), XC: \(gravityInDeviceRefFrame.x)")
                print("YB: \(gravityInDeviceRefFrame.y), YC: \(-gravityInDeviceRefFrame.y)")
                print("ZB: \(gravityInDeviceRefFrame.z), ZC: \(-gravityInDeviceRefFrame.z)")
            })
        }
        }
        if sensorDevice == .ACCELEROMETER{
            if motion.isDeviceMotionAvailable{
                motion.deviceMotionUpdateInterval = 1.0/60.0
                self.motion.startAccelerometerUpdates()
                motion.startDeviceMotionUpdates(using: .xArbitraryZVertical, to: OperationQueue.current!, withHandler: {
                    (data,error) in
                    guard let gravityInDeviceRefFrame = self.motion.accelerometerData, error == nil else {
                        print(error?.localizedDescription ?? "Nil")
                        return
                    }
                    let XC = gravityInDeviceRefFrame.acceleration.x
                    let YC = -(gravityInDeviceRefFrame.acceleration.y)
                    let ZC = -(gravityInDeviceRefFrame.acceleration.z)
                    
                    self.A = XC
                    self.B = YC
                    self.C = -(XC*400) - (YC*600) + ZC*98.267716535
                    print("XB: \(gravityInDeviceRefFrame.acceleration.x), XC: \(gravityInDeviceRefFrame.acceleration.x)")
                    print("YB: \(gravityInDeviceRefFrame.acceleration.y), YC: \(-gravityInDeviceRefFrame.acceleration.y)")
                    print("ZB: \(gravityInDeviceRefFrame.acceleration.z), ZC: \(-gravityInDeviceRefFrame.acceleration.z)")
                })
            }
        }
    }

    
    /* Stop reporting CoreMotion updates */
    func stopCoreMotion(){
        motion.stopAccelerometerUpdates()
        motion.stopDeviceMotionUpdates()
        self.A = 0
        self.B = 0
        self.C = 0
    }
    
    // Your code here
    // ...
}
