//
//  ViewController.swift
//  Swift_5_Assign_3
//
//  Created by renpeng on 2021/5/5.
//

import UIKit
import AVFoundation
import CoreMotion


/* Enum for type of sensor device in use */
enum SensorDevice : Int {
    case DEVICE_MOTION
    case ACCELEROMETER
}

class ViewController: UIViewController, AVCaptureVideoDataOutputSampleBufferDelegate{
    // MARK: Outlets setup
    @IBOutlet weak var imageView: UIImageView!
    @IBOutlet weak var promptLabel: UILabel!
    @IBOutlet weak var segmentControl: UISegmentedControl!
    @IBOutlet weak var sensorDeviceLabel: UILabel!
    
 
    // MARK: CoreMotion and AVFoundation setup
    var sensorDevice = SensorDevice.DEVICE_MOTION
    // Your code to setup and initialize CMMotionManager, AVCaptureSession
    // and/or any necessary object here
    // ...
    
    let motion = CMMotionManager()
    var captureSession: AVCaptureSession!
    
    //vars for passing data from the ViewController+CoreMotion file to ViewController+Camera
    var A = 0.0
    var B = 0.0
    var C = 0.0
    
    //a var to control when the line is displayed on the screen. 
    var showLine = true
    
    // MARK: ViewController Lifecycle
    override func viewDidLoad() {
        super.viewDidLoad()
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        setUpCamera()
        startCamera()
    }
    
    override func viewDidDisappear(_ animated: Bool) {
        super.viewDidDisappear(animated)
        setUpCamera()
    }
    
    
    // MARK: ViewController Action
    /* Whether to keep reporting CoreMotion updates */
    @IBAction func toggleSensorUpdates(_ sender: UIBarButtonItem) {
        if sender.title == "Start" {
            sender.title = "Stop"
            hideControlPanel(true)
            startCoreMotion()
            showLine = true //turn on horizon line
        }
        else {
            sender.title = "Start"
            hideControlPanel(false)
            stopCoreMotion()
            showLine = false //turn off horizon line
        }
    }
    
    /* Which type of sensor device in use for reporting CoreMotion updates */
    @IBAction func toggleSensorDevice(_ sender: UISegmentedControl) {
        switch sender.selectedSegmentIndex {
        case 0:
            sensorDevice = .DEVICE_MOTION
            sensorDeviceLabel.text = "Sensor Device : Device Motion"
        case 1:
            sensorDevice = .ACCELEROMETER
            sensorDeviceLabel.text = "Sensor Device : Accelerometer"
        default:
            break
        }
    }
    
    /* Helper function for displaying segment control and labels */
    private func hideControlPanel(_ isHidden: Bool){
        promptLabel.isHidden = isHidden
        segmentControl.isHidden = isHidden
    }
}
