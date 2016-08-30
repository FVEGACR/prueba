package facephi.plugin.usercontrol;

import android.content.Intent;
import android.os.Bundle;
import android.util.Base64;
import android.widget.Toast;

import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CallbackContext;

import org.apache.cordova.PluginResult;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.facephi.sdk.extractor.FinalDiagnostic;
import com.facephi.sdk.library.UCConfiguration;
import com.facephi.sdk.library.UCMode;
import com.facephi.sdk.library.UCResult;
import com.facephi.sdk.library.UserControlException;
import com.facephi.sdk.library.UserControlExceptionType;
import com.facephi.sdk.ui.FPhiUserControlAndroid;

import java.util.Iterator;

/**
 * This class echoes a string called from JavaScript. Launches the Android User Control.
 */
public class UCFacephi extends CordovaPlugin {

	public static final String WIZARD_REG = "WizardRegister";
	public static final String AUTHENTICATE = "Authenticate";
	public static final String WIZARD_LIV = "WizardLiveness";

	public CallbackContext _callbackContext;

	public boolean _isCordovaActivityDestroyed = false;

	/**
	 * Entry method from Javascript code. Executes the request and returns PluginResult.
	 *
	 * @param action	 		Is used to distinguish between different method calls that users may make to your plugin.
	 * @param args		 		Method arguments in JSON format.
	 * @param callbackContext	The callback id used when calling back into JavaScript.
	 * @return 					True if plugin handles a particular action, and "false" otherwise. Note that this does indicate the success or failure of the handling.
	 * 							Indicating success is failure is done by calling the appropriate method on the callbackContext. While our code only passes back a message
	 */
	@Override
	public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {

		_callbackContext = callbackContext;

		String mode = getUCMode(args);



		if (mode.equals(WIZARD_REG)) {
			UCConfiguration conf = new UCConfiguration(UCMode.WizardRegister);
			conf = getUCConfiguration(conf, args);
			this.launchActivityUC(conf, 100);
		}

		if (mode.equals(AUTHENTICATE)) {
			UCConfiguration conf = new UCConfiguration(UCMode.Authenticate);
			conf = getUCConfiguration(conf, args);
			this.launchActivityUC(conf, 101);
		}

		if (mode.equals(WIZARD_LIV)) {
			UCConfiguration conf = new UCConfiguration(UCMode.WizardLiveness);
			conf = getUCConfiguration(conf, args);
			this.launchActivityUC(conf, 102);
		}


		return true;
	}


	 /**
	 * Launches the User Control Activity selected by the user.
	 *
	 * @param conf	 			The User Control configuration
	 * @param operation			Index of the User Control operation
	 * @return 					True if plugin handles a particular action, and "false" otherwise. Note that this does indicate the success or failure of the handling.
	 * 							Indicating success is failure is done by calling the appropriate method on the callbackContext. While our code only passes back a message
	 */
	private boolean launchActivityUC(UCConfiguration conf, int operation) {
		// TODO
		// cordova.getActivity ().runOnUiThread (new Runnable () {

		try {
			Intent intent = new Intent(cordova.getActivity().getBaseContext(), FPhiUserControlAndroid.class);
			intent.putExtra("configuration", conf);

			PluginResult r = new PluginResult(PluginResult.Status.NO_RESULT);
			r.setKeepCallback(true);
			_callbackContext.sendPluginResult(r);

			cordova.startActivityForResult(this, intent, operation);
		} catch (Exception exc) {
			System.err.println("Exception: " + exc.getMessage());
			_callbackContext.error(exc.getMessage());
		}
		return true;
	}

	/**
	 * Processes the activity result from the User Control.
	 *
	 * @param requestCode	 	Code Request
	 * @param resultCode		Operation code
	 * @param data				Result of the User Control
	 */
	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		try {

			if(_isCordovaActivityDestroyed) {
				return;
			}

			if (requestCode == -1) {
				this._callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR,  new String()));
				return;
			}

			if (data == null) {
				this._callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR,  new String()));
				return;
			}

			UCResult ucResult = data.getParcelableExtra("result");
			OutputBundle output = new OutputBundle(ucResult);

			if (ucResult == null) {
				// Toast.makeText(cordova.getActivity().getBaseContext(), cordova.getActivity().getResources().getString(R.string.message_no_results), Toast.LENGTH_LONG).show();
				this._callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR,  new String()));
				return;
			}

			// at last call sendPluginResult
			if(output._finishStatus == 2) { // Es un error. Se envía al evento de error.
				this._callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, output.ReturnOutputJSON()));
			}
			else { // Ha salido sin producirse un error en el control de usuario, se gestiona en el evento de acierto.
				this._callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.OK, output.ReturnOutputJSON()));
			}
		} catch (Exception exc) {
			System.err.println("Exception: " + exc.getMessage());
			this._callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, new String()));
			this._callbackContext.error(exc.getMessage());
		}
	}


	/**
	 * Processes the JSON input argument and gets the execution mode of the User Control.
	 *
	 * @param args		JSON array with input arguments.
	 * @return 			Mode of the user control
	 */
	private String getUCMode(JSONArray args) throws JSONException {
		UCConfiguration conf = new UCConfiguration();
		if(args == null || args.length() == 0)
			return "";

		JSONObject actualObject = args.getJSONObject(0);

		Iterator iterator = actualObject.keys();
		while(iterator.hasNext()){
			String key = (String)iterator.next();
			if(key.equalsIgnoreCase("mode")) {
				String issue = actualObject.getString(key);
				return issue;
			}
		}
		return "";
	}



	/**
	 * Processes the JSON input argument and sets the configuration of the User Control.
	 *
	 * @param args		JSON array with input arguments.
	 * @return 			Configuration of the user control
	 */
	private UCConfiguration getUCConfiguration(UCConfiguration conf, JSONArray args) throws JSONException {
		if(args == null || args.length() == 0)
			return conf;

		JSONObject actualObject = args.getJSONObject(0);

		Iterator iterator = actualObject.keys();
		while(iterator.hasNext()){
			String key = (String)iterator.next();
			if(key.equalsIgnoreCase("config")) {
				JSONObject issue = actualObject.getJSONObject(key);
				boolean enableImages = issue.optBoolean("enableImages");
				double sceneTimeout = issue.optDouble("sceneTimeout");
				double cropPercent = issue.optDouble("cropPercent");
				boolean debug = issue.optBoolean("debug");
				boolean crop = issue.optBoolean("crop");

				conf.enableImages(enableImages);
				conf.setSceneTimeout((float)sceneTimeout);
				if(conf.getExtractionConfig() != null) conf.getExtractionConfig().setCropImagePercent((float)cropPercent);
				if(conf.getExtractionConfig() != null) conf.getExtractionConfig().setCropImageDebug(crop);
				conf.setDebug(debug);

			}
		}
		return conf;
	}


	
	/**
	 * Called when the Activity is being destroyed (e.g. if a plugin calls out to an
	 * external Activity and the OS kills the CordovaActivity in the background).
	 * The plugin should save its state in this method only if it is awaiting the
	 * result of an external Activity and needs to preserve some information so as
	 * to handle that result; onRestoreStateForActivityResult() will only be called
	 * if the plugin is the recipient of an Activity result
	 *
	 * @return  Bundle containing the state of the plugin or null if state does not
	 *          need to be saved
	 */
	public Bundle onSaveInstanceState() {
		return null;
	}

	/**
	 * Called when a plugin is the recipient of an Activity result after the
	 * CordovaActivity has been destroyed. The Bundle will be the same as the one
	 * the plugin returned in onSaveInstanceState()
	 *
	 * @param state             Bundle containing the state of the plugin
	 * @param errorCallbackContext   Replacement Context to return the plugin result to
	 */
	public void onRestoreStateForActivityResult(Bundle state, CallbackContext errorCallbackContext) {
		this._isCordovaActivityDestroyed = true;
		UCResult ucResult = new UCResult();
		ucResult.setException(new UserControlException(UserControlExceptionType.HardwareError));
		OutputBundle _outputBundle = new OutputBundle(ucResult);

		try {
			errorCallbackContext.sendPluginResult(new PluginResult(PluginResult.Status.OK, _outputBundle.ReturnOutputJSON()));
			this._callbackContext = errorCallbackContext;
		} catch (JSONException e) {
			e.printStackTrace();
		}

		return;

	}
}
