//
//  NSDate+Utils.h
//  iCashier
//
//  Created by Radoslav Danko on 07/02/2014.
//  Copyright (c) 2018 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, TimeUnitsEnum) {
    TimeUnitsEnumSeconds=0,
    TimeUnitsEnumMinutes,
    TimeUnitsEnumHours,
    TimeUnitsEnumDays,
    TimeUnitsEnumMonths,
    TimeUnitsEnumYears
} ;

@interface NSDate (Utils)
-(NSDate *)GMTnoon;
+(NSDate *)todayFirstInstant;
+(NSDate *)yesterdayLastInstant;
+(NSDate *)yesterdayFirstInstant;
-(BOOL)isStillToday;
-(NSDate *)oneDayAgo;
-(NSDate *)sevenDaysAgo;
-(NSUInteger)dayOrdinalForItsWeek;
-(NSDate *)firstDateOfWeek;
-(NSDate *)firstDateOfLastWeek;
-(NSDate *)firstDateOfLastTwoWeeks;
-(NSDate *)lastDateOfLastWeek;
-(NSDate *)firstDateOfMonth;
-(NSDate *)firstDateOfQuarter;
-(NSDate *)firstMonthOfYear;
-(NSDate *)lastMonthOfYear;
-(NSDate *)firstMonthOfLastQuarterOfYear;
-(NSDate *)lastInstantOfYear;
-(NSDate *)firstMonth5YearsAgo;
-(NSDate *)firstDateOfLastSevenWeeks;
+(BOOL)isDateLater:(NSDate*)left than:(NSDate*)right;
-(BOOL)isDateSoonerThan:(NSDate*)right;
+(NSInteger)getCurrentYear:(NSDate*)aDate;
+(NSDate*)displaceDateInTimeUnits:(NSDate*)aDate amount:(NSInteger)amount timeUnit:(NSInteger)units;
+ (NSDate *)dateWithDate:(NSDate *)date Hour:(NSInteger)hour Minute:(NSInteger)minute Second:(NSInteger)second andTimeZone:(NSString*)timeZone;
-(NSString *)asStringWithFormat:(NSString *)format;
-(NSInteger)daysAgo;

@end
