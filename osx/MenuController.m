#import "MenuController.h"

@implementation MenuController

- (IBAction)defaultConfig:(id)sender
{
}

- (IBAction)doBackup:(id)sender
{
}

- (IBAction)doRestore:(id)sender
{
}

- (IBAction)getDirlist:(id)sender
{
}

- (IBAction)getIDList:(id)sender
{
}

- (IBAction)getScreen:(id)sender
{
}

- (IBAction)installShell:(id)sender
{
}

- (IBAction)isReady:(id)sender
{
}

- (IBAction)newWindow:(id)sender
{
}

- (IBAction)probeCalc:(id)sender
{
}

- (IBAction)probeLink:(id)sender
{
}

- (IBAction)receiveFLASHApp:(id)sender
{
}

- (IBAction)receiveVar:(id)sender
{
}

- (IBAction)remoteControl:(id)sender
{
}

- (IBAction)romDump:(id)sender
{
}

- (IBAction)romVersion:(id)sender
{
}

- (IBAction)saveConfig:(id)sender
{
}

- (IBAction)sendAMS:(id)sender
{
}

- (IBAction)sendFLASHApp:(id)sender
{
}

- (IBAction)sendVar:(id)sender
{
}

- (IBAction)showPrefsSheet:(id)sender
{
    [NSApp beginSheet:prefsWindow
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];
           
    [NSApp runModalForWindow:prefsWindow];
    
    [NSApp endSheet:prefsWindow];
    [prefsWindow orderOut:self];
}

- (IBAction)showThanks:(id)sender
{
}

@end
