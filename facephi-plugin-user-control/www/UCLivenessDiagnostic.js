/**
 * Enum for liveness diagnostic. Only relevant if you are calling to authenticateLiveness.
 *
 * @class UCLivenessDiagnostic
 * @constructor
 */
UCLivenessDiagnostic = Object.freeze({ "NotRated ": 1, "PhotoDetected": 2, "LivenessDetected": 3, "Unsuccess": 4, "UnsuccessLowPerformance": 5, "UnsuccessGlasses": 6, "UnsuccessLight ": 7 });

var keysLivenessDiagnostic = Object.keys(UCLivenessDiagnostic).reduce(function (acc, key) {
    return acc[UCLivenessDiagnostic[key]] = key, acc;
}, {});

/**
 * Gets the integer value of the selected diagnostic.
 *
 * @method getEnumLivenessDiagnostic
 * @type   Integer
 */
UCLivenessDiagnostic.getEnumLivenessDiagnostic = function (ordinal) {
    return keysLivenessDiagnostic[ordinal];
}

// Exports enum for APP visibility
module.exports.UCLivenessDiagnostic = UCLivenessDiagnostic;
