//
//  WDCard.h
//   WDePOS
//
//  Created by Danko, Radoslav on 07/10/16.
//  Copyright © 2016 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WDDataTypes.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  @class WDCard
 *  @discussion Card data supplied by terminal, to be used in the payment processing through Wirecard payment infrastructure
 @code POS Entry Mode:
 □ PAN Entry Mode (Position 1-2 )
 01 Manual Entry
 02 Magnetic stripe read, but full unaltered contents not provided
 05 PAN auto entry via chip
 07 Auto-entry via contactless magnetic chip
 79 Chip card at chip-capable terminal was unable to process transaction using data on the chip or magnetic stripe on the card - therefore, PAN entry via manual entry
 80 Chip card at chip-capable terminal was unable to process transaction using data on the chip therefore the terminal defaulted to the magnetic stripe read for the PAN. This is referred to as fallback.
 90 Complete contents of magnetic stripe, track 2 have been read and checked
 91 Auto-entry via contactless magnetic stripe
 
 □ PIN Entry Capability (Position 3)
 1 Terminal has PIN entry capability
 2 Terminal does not have PIN entry capability (default)
 3 EMV & PIN Entry capability
 4 EMV capability
  **/

@interface WDCard : NSObject

@property (nullable, nonatomic, strong) NSString *cardBrand;

@property (nullable, nonatomic, strong) NSString *posEntryMode;

@property (nullable, nonatomic, strong) NSString *signatureImg;
/**
 * Issuer obtained from EMV data or from PAN
 */
@property (nullable, nonatomic, readonly) NSString *issuer;
/**
 * Card type CREDIT | DEBIT obtained based on AID or from PAN
 */
@property (nullable, nonatomic, readonly) NSString *type;
/**
 * Primary Account Number - masked, obtained from EMV
 */
@property (nullable, nonatomic, readonly) NSString *pan;
@end


/**
 *  @class WDCardEmvDUKPT
 *  @discussion Card Data supplied by extension reading the ICC supporting decryption on the Switch side using HSM
 **/
@interface WDCardEmvDUKPT : WDCard
@property (nonnull, nonatomic, readonly) NSString *emvData;
/**
 * @brief Create Card data with the card details obtained from the card IC - DUKPT
 * Only for terminals which are supported by Switch HSM
 * @param emvData - EMV data as read from Chip
 */
-(nullable instancetype)initWithEMV:(NSString * _Nonnull )emvData;
/**
 * Application label obtained from EMV data
 */
@property (nullable, nonatomic, readonly) NSString *applicationLabel;
/**
 * Cardholder name obtained from EMV data
 */
@property (nullable, nonatomic, readonly) NSString *cardholderName;
/**
 * Application Identifier obtained from EMV data
 */
@property (nullable, nonatomic, readonly) NSString *aid;
///**
// * Issuer obtained from EMV data or from PAN
// */
//-(NSString *)issuer;
///**
// * Card type CREDIT | DEBIT obtained based on AID or from PAN
// */
//-(NSString *)type;
/**
 * Card additional name e.g. Electron | V PAY | InterLink obtained based on AID
 */
@property (nullable, nonatomic, readonly) NSString *name;
///**
// * Primary Account Number - masked, obtained from EMV
// */
//-(NSString *)pan;
@end

/**
 *  @class WDCardMagstripeDUKPT
 *  @discussion Card Data supplied by extension reading the Magstripe supporting decryption on the PaymentEngine side
 **/
@interface WDCardMagstripeDUKPT : WDCard
@property (nonnull, nonatomic, readonly)    NSString *track2Data;
@property (nonnull, nonatomic, readonly)    NSString *ksn;
@property (nullable, nonatomic,readonly)    NSString *pinData;
@property (nullable, nonatomic,readonly)    NSString *pinKsn;

/**
 * @discussion Create Card data with the card details obtained from the Magstripe - DUKPT
 * Only for terminals which are supported by HSM connected to Switch
 * @param track2Data - Track 2 data
 * @param ksn - data encryption KSN
 * @param pinData - if online PIN validation to be performed
 * @param pinKsn - if pindData supplied the pin KSN
 * @param pan - if masked pan is available
 */
-(nullable instancetype)initWithMagstripe:(NSString * _Nonnull )track2Data
                                      ksn:(NSString * _Nonnull)ksn
                                  pinData:(NSString * _Nullable)pinData
                                   pinKsn:(NSString * _Nullable)pinKsn
                                   pan:(NSString * _Nullable)pan;
/**
 * Cardholder name obtained from Track1 data
 */
@property (nullable, nonatomic, readonly) NSString *cardholderName;
@end


/**
 *  @class WDCardPassThroughDUKPT
 *  @discussion Card Data supplied by extension supporting decryption on the PaymentEngine side
 **/
@interface WDCardPassThroughDUKPT : WDCard
@property (nonnull, nonatomic, readonly)    NSString *track2Data;
@property (nonnull, nonatomic, readonly)    NSString *pan;
@property (nonnull, nonatomic, readonly)    WDEncryptionParameters *dataEncryptionParams;
@property (nullable, nonatomic,readonly)    NSString *pinData;
@property (nullable, nonatomic, readonly)   WDEncryptionParameters *pinEncryptionParams;

@end

/**
 *  @class WDCardEmvPassThroughDUKPT
 *  @discussion Card Data supplied by extension reading the ICC supporting decryption on the PaymentEngine side
 **/
@interface WDCardEmvPassThroughDUKPT : WDCardPassThroughDUKPT
@property (nonnull, nonatomic, readonly, getter = emvData)    NSString *emvData;

/**
 * @brief Create Card data with the card details obtained from the card IC - PassThrough DUKPT
 * @param emvData - EMV data as read from Chip
 * @param track2Data - Track 2 data
 * @param pan - masked PAN
 * @param posEntryMode - POS entry mode
 * @param dataEncryption - optional - can be nil in the case SRED data, SRED KSN, PIN data and PIN KSN are encoded in the designated EMV tags
 * @param pinData - if online PIN validation to be performed
 * @param pinEncryption - if pindData supplied the encryption details must be supplied too
 */
-(nullable instancetype)initWithEMV:(NSString * _Nonnull )emvData
                             track2:(NSString *_Nonnull)track2Data
                                pan:(NSString * _Nonnull)pan
                       posEntryMode:(NSString * _Nonnull)posEntryMode
                     dataEncryption:(WDEncryptionParameters * _Nullable)dataEncryption
                            pinData:(NSString * _Nullable)pinData
                      pinEncryption:(WDEncryptionParameters * _Nullable)pinEncryption
;
/**
 * Application label obtained from EMV data
 */
@property (nullable, nonatomic, readonly) NSString *applicationLabel;
/**
 * Cardholder name obtained from EMV data
 */
@property (nullable, nonatomic, readonly) NSString *cardholderName;
/**
 * Application Identifier obtained from EMV data
 */
@property (nullable, nonatomic, readonly) NSString *aid;
/**
 * Issuer obtained from EMV data or from PAN
 */
@property (nullable, nonatomic, readonly) NSString *issuer;
/**
 * Card type CREDIT | DEBIT obtained based on AID or from PAN
 */
@property (nullable, nonatomic, readonly) NSString *type;
/**
 * Card additional name e.g. Electron | V PAY | InterLink obtained based on AID
 */
@property (nullable, nonatomic, readonly) NSString *name;
@end


/**
 *  @class WDCardMagstripePassThroughDUKPT
 *  @discussion Card Data supplied by extension reading the Magstripe supporting decryption on the PaymentEngine side
 **/
@interface WDCardMagstripePassThroughDUKPT : WDCardPassThroughDUKPT

/**
 * @discussion Create Card data with the card details obtained from the Magstripe - PassThrough DUKPT
 * @param track2Data - Track 2 data
 * @param pan - masked PAN
 * @param posEntryMode 3 digit code see WDCardData POS Entry Mode
 * @param dataEncryption - data encryption details
 * @param pinData - if online PIN validation to be performed
 * @param pinEncryption - if pindData supplied the encryption details must be supplied too
 */
-(nullable instancetype)initWithMagstripe:(NSString * _Nonnull )track2Data
                                      pan:(NSString * _Nonnull)pan
                             posEntryMode:(NSString * _Nonnull)posEntryMode
                           dataEncryption:(WDEncryptionParameters * _Nullable)dataEncryption
                                  pinData:(NSString * _Nullable)pinData
                            pinEncryption:(WDEncryptionParameters * _Nullable)pinEncryption;

@property (nonatomic,strong, getter=pan, setter=setPan:) NSString *pan;
@end


NS_ASSUME_NONNULL_END
