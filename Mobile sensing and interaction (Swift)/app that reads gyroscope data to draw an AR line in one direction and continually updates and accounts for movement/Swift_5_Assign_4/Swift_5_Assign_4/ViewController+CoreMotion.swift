//
//  ViewController+CoreMotion.swift
//  Swift_5_Assign_3
//
//  Created by renpeng on 2021/5/5.
//

import Foundation
import CoreMotion
import UIKit
import AVFoundation

extension ViewController{

    
    /* Start reporting CoreMotion updates */
    func startCoreMotion(){
        // Your code here to start any sensor updates
        // ...
        if sensorDevice == .DEVICE_MOTION{
        if motion.isDeviceMotionAvailable{
            motion.deviceMotionUpdateInterval = 1.0/10.0
            self.motion.startAccelerometerUpdates()
            motion.startDeviceMotionUpdates(using: .xArbitraryZVertical, to: OperationQueue.current!, withHandler: {
                (data,error) in
                guard let attitude = data?.attitude, error == nil else {
                    print(error?.localizedDescription ?? "Nil")
                    return
                }
                self.motion.stopAccelerometerUpdates()
                self.attitudematrix = attitude.rotationMatrix
            })
        }
        }
        
        if sensorDevice == .ACCELEROMETER{
            if motion.isGyroAvailable{
                motion.gyroUpdateInterval = 1.0/10.0
                motion.deviceMotionUpdateInterval = 1.0/10.0
                self.motion.startAccelerometerUpdates()
                motion.startGyroUpdates( to: OperationQueue.current!, withHandler: {
                    (data,error) in
                    guard let gyro = data, error == nil else {
                        print(error?.localizedDescription ?? "Nil on getting gyro data")
                        return
                    }
                    guard let gravityInDeviceRefFrame = self.motion.accelerometerData, error == nil else {
                        print(error?.localizedDescription ?? "Nil")
                        return
                    }
                    let XC = gravityInDeviceRefFrame.acceleration.x
                    let YC = -(gravityInDeviceRefFrame.acceleration.y)
                    let ZC = -(gravityInDeviceRefFrame.acceleration.z)
                    self.alpha = atan2(YC, ZC)
                    self.beta = asin(-(XC))
                    self.rotationRate = gyro.rotationRate
                    self.count += 1
                    self.update_rotation()
            
                })
            }
        }
    }

    
    /* Stop reporting CoreMotion updates */
    func stopCoreMotion(){
        motion.stopGyroUpdates()
        motion.stopDeviceMotionUpdates()
        self.motion.stopAccelerometerUpdates()
        self.rotationRate = CMRotationRate()
        self.alpha = 0
        self.beta = 0
        self.count = 0
    }
    
    // Your code here
    // ...
}
