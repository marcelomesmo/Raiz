#ifndef FADEOUT_H
#define FADEOUT_H

#include "Transition.h"

/**
 * @brief      A Transition to Fade Out from a given Color.
 *
 * @author     marcelomesmo
 */
class FadeOut : public Transition
{
public:
	/**
	 * @brief      Create a new Fade Out transition.
	 *
	 * @param[in]  c     The Color we are going to Fade Out from.
	 */
	FadeOut(Color* c = Color::Black);
	/**
	 * @brief      Create a new Fade Out Transition.
	 *
	 * @param[in]  c     The Color we are going to Fade Out from.
	 * @param[in]  time  The time it takes for the transition to finish.
	 */
	FadeOut(Color* c, Uint32 time = 500);

	/**
	 * @brief      Updates the transition effects.
	 *
	 * @param      game   The running Game object.
	 * @param[in]  delta  The amount of time in miliseconds since last update.
	 */
	void update(Game* game, float delta);
	/**
	 * @brief      Render the Transition before the current Scene rendering.
	 *
	 * @param      g     The Graphics context to use for rendering.
	 */
	void preRender(Graphics& g);
	/**
	 * @brief      Render the Transition after the current Scene rendering.
	 *
	 * @param      g     The Graphics context to use for rendering.
	 */
	void postRender(Graphics& g);
	
	/**
	 * @brief      Check if the Transition has finished.
	 *
	 * @return     True if the Transition is complete.
	 */
	bool isFinished();

	/**
	* @brief      Set Transition color. Change Color but keep the Alpha.
	*
	* @param[in]  c      A Color parameter.
	* @param[in]  alpha  Alpha value of the Transition.
	*/
	void setColor(Color* c);

private:
	/**
	 * The Color to Fade In from.
	 */
	Color* cor;
	/**
	 * Current Color alpha value.
	 */
	float alpha;
	/**
	 * The time it takes for the transition to finish.
	 */
	Uint32 fadeTime;
};

#endif
