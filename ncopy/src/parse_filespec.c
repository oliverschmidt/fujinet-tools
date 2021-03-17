/**
 * Network Testing tools
 *
 * ncopy - copy files 
 *  N:<->D: D:<->N: or N:<->N:
 *
 * Author: Thomas Cherryhomes
 *  <thom.cherryhomes@gmail.com>
 *
 * Released under GPL 3.0
 * See COPYING for details.
 */

#include <stdbool.h>
#include <string.h>
#include "conio.h"
#include "parse_filespec.h"

bool parse_filespec(Context *context)
{  
  // Find comma.
  context->sourceDeviceSpec=strtok(context->buf,",");
  
  if (context->sourceDeviceSpec==NULL)
    {
      print("NO COMMA\x9b");
      return false;
    }

  context->destDeviceSpec=strtok(NULL,",");

  // Skip over whitespace
  while (*context->destDeviceSpec==0x20) { context->destDeviceSpec++; }
  
  // Put EOLs on the end.
  context->sourceDeviceSpec[strlen(context->sourceDeviceSpec)]=0x9B;
  context->destDeviceSpec[strlen(context->destDeviceSpec)]=0x9B;

  // Check for valid device name chars
  if (context->sourceDeviceSpec[0]<0x41 || context->sourceDeviceSpec[0]>0x5A)
    return false;
  else if (context->destDeviceSpec[0]<0x41 || context->destDeviceSpec[0]>0x5A)
    return false;

  // Check for proper colon placement
  if (context->sourceDeviceSpec[1]!=':' && context->sourceDeviceSpec[2]!=':')
    return false;
  else if (context->destDeviceSpec[1]!=':' && context->destDeviceSpec[2]!=':')
    return false;

  // Try to assign unit numbers.
  if (context->sourceDeviceSpec[1] != ':')
    context->sourceUnit=context->sourceDeviceSpec[1]-0x30;
  if (context->destDeviceSpec[1] != ':')
    context->destUnit=context->destDeviceSpec[1]-0x30;
  
  return true;
}
