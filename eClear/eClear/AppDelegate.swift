//
//  AppDelegate.swift
//  test787
//
//  Created by Pulik, Jaroslav on 17/11/2019.
//  Copyright © 2020 Wirecard. All rights reserved.
//

import UIKit
import WDePOS
import TWMessageBarManager

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow?
    
    @objc public var sdk: WDePOS?
    @objc public var backends: NSArray = []
    @objc public private(set) var language: String = "en"

    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        // Override point for customization after application launch.
        if backends.count == 0 {
            getAllBackendURLs()
        }
        
        return true
    }

    func applicationWillResignActive(_ application: UIApplication) {
        // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
        // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
    }

    func applicationDidEnterBackground(_ application: UIApplication) {
        // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
        // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    }

    func applicationWillEnterForeground(_ application: UIApplication) {
        // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
    }

    func applicationDidBecomeActive(_ application: UIApplication) {
        // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    }

    func applicationWillTerminate(_ application: UIApplication) {
        // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    }


}

extension AppDelegate {

    public func loginUser(
        _ username: String,
        password: String,
        backend: String,
        completion: @escaping (_ success: Bool) -> Void
    ) {
        sdk = WDePOS.sharedInstance()
        sdk?.setup(
            with: WDEnvironmentFromUrl(backend),
            username: username,
            password: password
        ) { [weak self] (currentUser, cashier, error) in
            if let error = error {
                self?.showError("Login", text: error.localizedDescription)
            }
            completion(currentUser != nil && error == nil)
        }
    }
    
    private func getAllBackendURLs() {
        var filePath: String? = Bundle.main.path(forResource: "switchBE", ofType: "json")
        if filePath == nil {
            filePath = Bundle(for: self.classForCoder).path(forResource: "switchBE", ofType: "json")
        }
        guard let path = filePath else { return }
        guard let data: NSData = NSData(contentsOfFile: path) else { return }
        guard let dictBackents = try? JSONSerialization.jsonObject(with: data as Data) as? [String: Any] else { return }
        backends = (dictBackents["backends"] as? NSArray) ?? []
    }
    
}

extension AppDelegate {
    
    @objc
    public func showInfo(_ title: String, text: String?) {
        TWMessageBarManager.sharedInstance().showMessage(withTitle: title, description: text, type: .info)
    }
    
    @objc
    public func showError(_ title: String, text: String?) {
        TWMessageBarManager.sharedInstance().showMessage(withTitle: title, description: text, type: .error)
    }
    
    @objc
    public func showSuccess(_ title: String, text: String?) {
        TWMessageBarManager.sharedInstance().showMessage(withTitle: title, description: text, type: .success)
    }
    
}
