//
//  ViewController.swift
//  Swift_5_Assign_2
//
//  Created by renpeng on 2021/4/22.
//

import UIKit
import CoreMotion
import AudioToolbox.AudioServices

class ViewController: UIViewController {
    // MARK: Outlets setup
    var up = UpTime()!
    @IBOutlet weak var measurementLabel: UITextView!
    @IBOutlet weak var magnitudeLabel: UITextView!
    @IBOutlet weak var totalStepLabel: UILabel!
    @IBOutlet weak var buttonOutlet: UIButton!
    var timer: Timer?
    let motion = CMMotionManager()
    
    // MARK: Variables setup
    var isStart : Bool = false
    
    // MARK: ViewController Life-cycle
    override func viewDidLoad() {
        super.viewDidLoad()
        resetOutlets()
    }
    
    // MARK: ViewController functions
    @IBAction func buttonPressed() {
        if isStart {
            buttonOutlet.setBackgroundImage(UIImage(named:"start"), for: .normal)
            stopAccelerometer()
        }
        else {
            buttonOutlet.setBackgroundImage(UIImage(named:"stop"), for: .normal)
            startAccelerometer()
        }
        isStart = !isStart
    }
    
    /* Helper function for updating the measurement label on screen */
    func updateMeasurementLabel(_ data: CMAcceleration){
        measurementLabel.text = NSString.localizedStringWithFormat("x : %.5f\ny : %.5f\nz : %.5f\n", data.x, data.y, data.z) as String
    }
    
    /* Helper function for clearing all labels on screen */
    func resetOutlets(){
        measurementLabel.text = ""
        magnitudeLabel.text = "Acceleration Magnitude"
        totalStepLabel.text = "Total Step: 0"
    }
    
    /* YOUR TASKS */
    
    //Starts accelerometers with 60 updates per second
    func startAccelerometer(){
        self.up.step = 0
        if self.motion.isAccelerometerAvailable{
            self.motion.accelerometerUpdateInterval = 1.0 / 60.0
            self.motion.startAccelerometerUpdates()
            
            self.timer = Timer(fire: Date(), interval: (1.0/60.0), repeats: true, block: { (timer) in
                if let data = self.motion.accelerometerData{
                    let x = data.acceleration.x
                    let y = data.acceleration.y
                    let z = data.acceleration.z
                    let mag = (pow(x,2) + pow(y,2) + pow(z,2)).squareRoot()
                    self.up.UpTimes(mag: mag - 1.0)
                    if self.up.state == 6 {
                        AudioServicesPlaySystemSound(kSystemSoundID_Vibrate)
                    }
                    self.measurementLabel.text = "x axis: " + String(format: "%f", x) + "\n" + "y axis: " + String(format: "%f", y) + "\n" + "z axis: " + String(format: "%f", z)
                    self.magnitudeLabel.text = "Magnitude" + String(format: "%f", mag)
                }
            })
            RunLoop.current.add(self.timer!, forMode: RunLoop.Mode.default)
        }
    }

    //Stops accelerometers from collecting data. Used in the even the user pushes the button
    func stopAccelerometer(){
        if self.motion.isAccelerometerAvailable{
            self.motion.stopAccelerometerUpdates()
            totalStepLabel.text = "Total Steps: " + String(up.step)
        }
    }

}
