#include "showasset.hpp"

ShowAsset::ShowAsset(vector<string> args)
{
  // sets the socket type and return code
  this->socketType = "TCP";
  this->returnCode = RES_SHOW_ASSET;

  // parses the arguments
  this->aid = args[0];

  if (!Verify::isAID(this->aid)){
    printf("aid argument is invalid\n");
    throw exception();
  }
}

void ShowAsset::execute(){
  if (!auctionExists(this->aid)){
    return this->send(STATUS_NOK);
  }

  // Get the asset
  string asset = getAuctionAsset(this->aid);

  // If there are no assets, return NOK
  if (asset.empty()) {
    return this->send(STATUS_NOK);
  }

  // Return the asset
  return this->send(STATUS_OK + string(" ") + asset);
}