/****************************************************************
 *                      Capabilities Receive.c                  *
 *                                                              *
 * The following program is a console application that          *
 * demonstrates how to implement capabilities receiving using   *
 * the RADVISION H.323 Protocol Stack.                          *
 * The program does the following :                             *
 *                                                              *
 * 1. Gets the host IP address and displays it on the screen    *
 *    of the sending side.                                      *
 * 2. Initializes the H.323 Stack.                              *
 * 3. Installs the H.323 Stack call and control callbacks.      *
 * 4. Waits for an incoming call and when it arrives, prompts   *
 *    the user to answer it.                                    *
 * 5. When the capabilities are accepted, the function displays *
 *    the channel types that the remote party supports.         *
 * 6. The receiving side can choose to drop the call.           *
 ****************************************************************/



#include "../osDependency.h"
#include <seli.h>
#include <cm.h>



/* The application handle. */
HAPP hApp;

/* Boolean indicator for terminating the application */
static RvBool stop = RV_FALSE;

/* Stores the call state. */
RvUint32 call_st;

/* The Stack handle to the call. */
HCALL hs_Call;

/* The application handle. */
HPVT pvtTree;

/* The remote terminal capability message PVT Node ID. */
RvPvtNodeId cap;


/****************************************************************
 * inputHandler                                                 *
 * Purpose    : This is a callback function that is called      *
 *              whenever the user presses a key on the keyboard.*
 *              The function decides how to proceed according   *
 *              to the call state.                              *
 *              The key that was pressed is usually a response  *
 *              to a prompt for the user in the early stages of *
 *              the program.                                    *
 * Input      : fd       : File descriptor that you want to     *
 *                         register with seli.                  *
 *              seliEvent: The event that called the callback   *
 *                         function.                            *
 *              error    : If an error occurs, the value is 1.  *
 *                         If no error occurs, the value        *
 *                         remains 0.                           *
 ****************************************************************/
static void RVCALLCONV inputHandler(int        fd,
                                    seliEvents sEvent,
                                    RvBool     error)
{
    int answer;

    RV_UNUSED_ARG(fd);
    RV_UNUSED_ARG(sEvent);
    RV_UNUSED_ARG(error);

    /* Reads the user input */
    answer = getchar();

    /* If the answer is positive: */
    if (answer == 'y')
    {
        switch(call_st)
        {
        case cmCallStateOffering:
            /* The user answers the call. */
            printf("Answering the call\n");
            cmCallAnswer(hs_Call);
            break;

        case cmCallStateConnected:
            /* The user drops the call. */
            printf("Dropping the call.\n");
            cmCallDrop(hs_Call);
            break;

        case cmCallStateIdle:
            /* The user closes the window and disconnects the Q.931 channel.
                When stop!=0, the loop in the main function stops running. */
            printf("Bye-bye\n");
            stop = RV_TRUE;
            break;

        default:
            break;
        }
    }

    /* If the answer is not positive: */
    if (answer == 'n')
    {
        /* The user does not take the call and the application drops it.*/
        if (call_st == cmCallStateOffering)
        {
            printf("I don't want to take the call\n");
            cmCallDrop(hs_Call);
        }
    }

    if (stop)
        endKeyboardInput();
}


/****************************************************************
 * cmEvCallStateChanged                                         *
 * Purpose : This is the callback function used by the Stack to *
 *           report a change in the status of a call to the     *
 *           application.                                       *
 * Input   : haCall   :The application handle for the call.     *
 *           hsCall   :The Stack handle for the call.           *
 *           state    :The new state of the call.               *
 *           stateMode:New state mode. This parameter describes *
 *                     how or why the call enters a new state.  *
 * Return  : If an error occurs, the function returns a negative*
 *           value.                                             *
 *           If no error occurs, the function returns a         *
 *           non-negative value.                                *
 ****************************************************************/
static int RVCALLCONV cmEvCallStateChanged(IN   HAPPCALL           haCall,
                                           IN   HCALL              hsCall,
                                           IN   cmCallState_e      state,
                                           IN   cmCallStateMode_e  stateMode)
{
    RV_UNUSED_ARG(haCall);

    /* The global variable for the Stack handle. */
    hs_Call = hsCall;

    switch(state)
    {

    /* This callback function is called with the following state when
       the Stack receives a call offering. The user is prompted to
       answer the call. The user response is read by the inputHandler
       function. */

    case cmCallStateOffering:
        call_st = cmCallStateOffering;
        printf("Receiving a call offering\n");
        printf("If you want to answer, enter 'y'.\n");
        break;

    /* The callback function is called with this state when the call is
       fully connected (both H.245 and Q.931 call establishment
       processes are completed).*/

    case cmCallStateConnected:
        if (stateMode==cmCallStateModeConnectedCall)
        {
            call_st = cmCallStateConnected;
            printf("If you want to drop the call, enter 'y'.\n");
        }
        break;

    /* This callback function is called with the following state after
       the call is disconnected. The 'cmCallClose' function is called
       and the user is then prompted to close the application. */

    case cmCallStateIdle:
        call_st = cmCallStateIdle;
        cmCallClose(hsCall);
        printf("The call is closed\n");
        printf("If you want to close the window, enter 'y'.\n");
        break;

    default:
        break;
    }

    return RV_OK;
}


/****************************************************************
 * cmEvCallCapabilities                                         *
 * Purpose : This is the callback function used by the Stack to *
 *           report changes in the remote party�s capabilities. *
 *           The function reports only the types of channels    *
 *           that the remote party supports.                    *
 * Input   : haCall      : The application handle for the call. *
 *           hsCall      : The Stack handle for the call.       *
 *           capabilities: Null-terminated array of structures  *
 *                         containing capability information.   *
 * Return  : If an error occurs, the function returns a negative*
 *           value.                                             *
 *           If no error occurs, the function returns a         *
 *           non-negative value.                                *
 ****************************************************************/
int RVCALLCONV
cmEvCallCapabilities(IN         HAPPCALL        haCall,
                     IN         HCALL           hsCall,
                     IN         cmCapStruct*    capabilities[])
{
    /* Number of entries in the table. */
    int noOfEntries;
    int i;

    RV_UNUSED_ARG(haCall);

    pvtTree = cmGetValTree(hApp);

    /* Node ID of the capability message. */
    cap = cmCallGetRemoteCapabilities(hsCall);

    /* Gets the number of entries from the capability table node ID. */
    pvtGetByPath(pvtTree, cap, "capabilityTable" , NULL, &noOfEntries, NULL);

    printf ("The channels the remote party supports:\n\n");

    for(i=0; i<noOfEntries; i++)
    {
        printf("Channel %d: %s\n",i, capabilities[i]->name);
        if (capabilities[i]->direction == cmCapReceive)
            printf("direction: receive\n");
        if (capabilities[i]->direction == cmCapTransmit)
            printf("direction: transmit\n");
        if (capabilities[i]->direction == cmCapReceiveAndTransmit)
            printf("direction: receive and transmit\n");
    }

    return RV_OK;
}


int AppMain(int argc, char* argv[])
{
    RvChar addrStr[64];

    /* The structure which stores IP address and port.*/
    cmRASTransport tr;

    /* The structures that contain pointers to the callback functions. */
    SCMCALLEVENT cmCallEvent;
    SCMCONTROLEVENT cmControlEvent;

    RV_UNUSED_ARG(argc);
    RV_UNUSED_ARG(argv);

    /* Initialize the structures that contain pointers to the callback functions. */
    memset(&cmCallEvent, 0, sizeof(SCMCALLEVENT));
    memset(&cmControlEvent, 0, sizeof(SCMCONTROLEVENT));
    cmCallEvent.cmEvCallStateChanged = cmEvCallStateChanged;
    cmControlEvent.cmEvCallCapabilities = cmEvCallCapabilities;

    /* Initializes the Stack according to the EPconfig.val file. */
    if (cmInitialize(GetFilename("EPConfig.val"),&hApp) < 0 )
        return RV_ERROR_UNKNOWN;

    /* Sets the inputHandler function as the callback function whenever an event occurs. */
    setKeyboardInput(inputHandler);

    /* Sets the calls event handler function. */
    cmSetCallEventHandler(hApp,&cmCallEvent,sizeof(cmCallEvent));

    /* Sets the control event handler function. */
    cmSetControlEventHandler(hApp,&cmControlEvent,sizeof(cmControlEvent));

    /* Gets the host IP address and displays it on the screen. */
    cmGetLocalCallSignalAddress(hApp,&tr);
    cmTransportAddress2String(&tr, sizeof(addrStr), addrStr);
    printf("My address is: TA:%s\n", addrStr);

    /* This loop is responsible for activating the process that selects
       all registered file descriptors and calls the appropriate
       callback function when an event occurs. The loop stops when
       'stop'=1. This is performed by the callback function after a call
       has been connected and then disconnected. The user then prompts the
       application to terminate. */

    stop = RV_FALSE;
    while(!stop)
       seliSelect();

    /* Shuts down the H.323 Stack. */
    cmEnd(hApp);

    return 0;
}




const char* myValFile0[] = /* SOURCE = ./EPConfig.val */ {"EPConfig.val",
"# RADVISION H.323 Stack Configuration File",
"#",
"# Value encodings:",
"#    ''   -  String (and asciiz is not appended)",
"#    \"\"   -  BMP string of ASCII charactes",
"#    []   -  Hex octet string",
"#    <>   -  IP",
"#    {}   -  Object ID",
"#    %   -  Bit string",
"#   Other -  Integer",
"",
"",
"",
"1 h450system = 0",
"+  maxCalls = 10",
"   maxServices = 100",
"",
"",
"1 system = 0",
"+  maxCalls = 2",
"   maxChannels = 4",
"",
"",
"1 RAS = 0",
"+  responseTimeOut = 4",
"   manualRAS = 1",
"   maxFail = 1",
"   allowCallsWhenNonReg = 0",
"   manualRegistration = 0",
"   manualDiscovery = 0",
"+   defaultGatekeeper = 0",
"+    ipAddress = 0",
"+     ip = [7f000001]",
"      port = 1719",
"",
"2  registrationInfo = 0",
"+   terminalType = 0",
"+    vendor = 0",
"+     vendor = 0",
"+      t35CountryCode = 11",
"       t35Extension = 11",
"       manufacturerCode = 11",
"-     productId = 'Test application'",
"      versionId = 'RADVISION'",
"-    terminal = 0",
"     mc = 0",
"     undefinedNode = 0",
"-   terminalAlias = 0",
"+    * = 0",
"+     h323-ID = \"TEST\"",
"",
"2  rasMulticastAddress = 0",
"+   ipAddress = 0",
"+    ip = [e0000129]",
"     port = 1718",
"2  rasPort = 0",
"   compare15bitRasCrv = 1",
"   maxMulticastTTL = 10",
"",
"",
"1 Q931 = 0",
"+  responseTimeOut = 10",
"   connectTimeOut = 200",
"   callSignalingPort = 0",
"   maxCalls = 2",
"   manualCallProceeding = 0",
"   manualAccept = 0",
"",
"1 h245 = 0",
"+  masterSlave = 0",
"+   terminalType = 50",
"    timeout = 100",
"-  capabilities = 0",
"+   terminalCapabilitySet = 0",
"+    sequenceNumber = 0",
"     protocolIdentifier = [00]",
"     multiplexCapability = 0",
"+     h2250Capability = 0",
"+      maximumAudioDelayJitter = 60",
"       receiveMultipointCapability = 0",
"+       multicastCapability = 0",
"        multiUniCastConference = 0",
"        mediaDistributionCapability = 0",
"+        * = 0",
"+         centralizedControl = 0",
"          distributedControl = 0",
"          centralizedAudio = 0",
"          distributedAudio = 0",
"          centralizedVideo = 0",
"          distributedVideo = 0",
"",
"6      transmitMultipointCapability = 0",
"+       multicastCapability = 0",
"        multiUniCastConference = 0",
"        mediaDistributionCapability = 0",
"+        * = 0",
"+         centralizedControl = 0",
"          distributedControl = 0",
"          centralizedAudio = 0",
"          distributedAudio = 0",
"          centralizedVideo = 0",
"          distributedVideo = 0",
"",
"6      receiveAndTransmitMultipointCapability = 0",
"+       multicastCapability = 0",
"        multiUniCastConference = 0",
"        mediaDistributionCapability = 0",
"+        * = 0",
"+         centralizedControl = 0",
"          distributedControl = 0",
"          centralizedAudio = 0",
"          distributedAudio = 0",
"          centralizedVideo = 0",
"          distributedVideo = 0",
"",
"6      mcCapability = 0",
"+       centralizedConferenceMC = 0",
"        decentralizedConferenceMC = 0",
"-      rtcpVideoControlCapability = 0",
"       mediaPacketizationCapability = 0",
"+       h261aVideoPacketization = 0",
"",
"4    capabilityTable = 0",
"+     * = 0",
"+      capabilityTableEntryNumber = 7111",
"       capability = 0",
"+       receiveAudioCapability = 0",
"+        g711Ulaw64k = 60",
"",
"5     * = 0",
"+      capabilityTableEntryNumber = 7110",
"       capability = 0",
"+       receiveAudioCapability = 0",
"+        g711Alaw64k = 60",
"",
"5     * = 0",
"+      capabilityTableEntryNumber = 728",
"       capability = 0",
"+       receiveAudioCapability = 0",
"+        g728 = 60",
"",
"5     * = 0",
"+      capabilityTableEntryNumber = 261",
"       capability = 0",
"+       receiveVideoCapability = 0",
"+        h261VideoCapability = 0",
"+         qcifMPI = 1",
"          cifMPI = 1",
"          temporalSpatialTradeOffCapability = 0",
"          maxBitRate = 600",
"          stillImageTransmission = 0",
"",
"5     * = 0",
"+      capabilityTableEntryNumber = 263",
"       capability = 0",
"+       receiveVideoCapability = 0",
"+        h263VideoCapability = 0",
"+         sqcifMPI = 1",
"          qcifMPI = 1",
"          cifMPI = 1",
"          maxBitRate = 1000",
"          unrestrictedVector = 0",
"          arithmeticCoding = 0",
"          advancedPrediction = 0",
"          pbFrames = 0",
"          temporalSpatialTradeOffCapability = 0",
"          errorCompensation = 0",
"",
"5     * = 0",
"+      capabilityTableEntryNumber = 120",
"       capability = 0",
"+       receiveAndTransmitDataApplicationCapability = 0",
"+        application = 0",
"+         t120 = 0",
"+          separateLANStack = 0",
"8        maxBitRate = 1000",
"",
"4    capabilityDescriptors = 0",
"+     * = 0",
"+      capabilityDescriptorNumber = 0",
"       simultaneousCapabilities = 0",
"+       * = 0",
"+        * = 7111",
"         * = 7110",
"         * = 728",
"-       * = 0",
"+        * = 261",
"         * = 263",
"-       * = 0",
"+        * = 120",
"",
"3   timeout = 100",
"-  channels = 0",
"+   * = 0",
"+    name = 'g711Alaw64k'",
"     dataType = 0",
"+     audioData = 0",
"+      g711Alaw64k = 60",
"",
"3   * = 0",
"+    name = 'g711Ulaw64k'",
"     dataType = 0",
"+     audioData = 0",
"+      g711Ulaw64k = 60",
"",
"3   * = 0",
"+    name = 'g728'",
"     dataType = 0",
"+     audioData = 0",
"+      g728 = 60",
"",
"3   * = 0",
"+    name = 'h261VideoCapability'",
"     dataType = 0",
"+     videoData = 0",
"+      h261VideoCapability = 0",
"+       qcifMPI = 1",
"        cifMPI = 1",
"        temporalSpatialTradeOffCapability = 0",
"        maxBitRate = 600",
"        stillImageTransmission = 0",
"",
"3   * = 0",
"+    name = 'h263VideoCapability'",
"     dataType = 0",
"+     videoData = 0",
"+      h263VideoCapability = 0",
"+       sqcifMPI = 1",
"        qcifMPI = 1",
"        cifMPI = 1",
"        maxBitRate = 1000",
"        unrestrictedVector = 0",
"        arithmeticCoding = 0",
"        advancedPrediction = 0",
"        pbFrames = 0",
"        temporalSpatialTradeOffCapability = 0",
"        errorCompensation = 0",
"",
"3   * = 0",
"+    name = 't120'",
"     dataType = 0",
"+     data = 0",
"+      application = 0",
"+       t120 = 0",
"+        separateLANStack = 0",
"6      maxBitRate = 1000",
"",
NULL};