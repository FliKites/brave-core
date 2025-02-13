// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import Amount from './amount'

/**
 * Converts a coins value from it's lowest denomination to it's highest
 * Wei → ETH
 * Lamport → SOL
 * @param weiValue coins value formatted in it's lowest denomination
 * @param assetDecimals the decimal amount the the asset uses for convertion
 * @returns
 */
export const weiToEther = (
  weiValue: string,
  assetDecimals: number
) => {
  return new Amount(weiValue)
    .divideByDecimals(assetDecimals)
}
