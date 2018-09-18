# Demo - train the style transfer network & use it to generate an image

from __future__ import print_function
from scipy import optimize

from train import train
from generate import generate
from utils import list_images
import sys
import os

# sys.path.append('~/24783/src/iLearn/Project/arbitrary_style_transfer')
user_content_path = str(sys.argv[1])  # content image path with image name
user_style_path = str(sys.argv[2])  # style image path with image name
save_path = str(sys.argv[3])  # output save directory
bbox_x1 = float(sys.argv[4])  # top left x
bbox_y1 = float(sys.argv[5])  # top left y
bbox_x2 = float(sys.argv[6])  # bottom right x
bbox_y2 = float(sys.argv[7])  # bottom right y

IS_TRAINING = False
PATH = os.path.dirname(os.path.realpath(__file__))

ENCODER_WEIGHTS_PATH = os.path.join(PATH, 'data/vgg19_normalised.npz')

STYLE_WEIGHTS = [2.0]

MODEL_SAVE_PATHS = [
    os.path.join(PATH, 'data/style_weight_2e0.ckpt')
]

# STYLES = [
#     'cat', 'mosaic', 'escher_sphere',
#     'lion', 'udnie', 'woman_matisse',
# ]

STYLES = [user_style_path]


def main():
    if IS_TRAINING:

        content_imgs_path = list_images('../MS_COCO')  # path to training content dataset
        style_imgs_path = list_images('../WikiArt')  # path to training style dataset

        for style_weight, model_save_path in zip(STYLE_WEIGHTS, MODEL_SAVE_PATHS):
            print('\nBegin to train the network with the style weight: %.2f ...\n' % style_weight)

            train(style_weight, content_imgs_path, style_imgs_path, ENCODER_WEIGHTS_PATH, model_save_path, debug=True)

            print('\nSuccessfully! Done training...\n')
    else:

        for style_name in STYLES:

            # print('\nUse "%s.jpg" as style to generate images:' % style_name)

            for style_weight, model_save_path in zip(STYLE_WEIGHTS, MODEL_SAVE_PATHS):
                # print('\nBegin to generate images with the style weight: %.2f ...\n' % style_weight)

                # contents_path = list_images('images/content')
                contents_path = [user_content_path]
                # style_path    = 'images/style/' + style_name + '.jpg'
                style_path = style_name
                # output_save_path = 'outputs'
                output_save_path = save_path
                style_name_only = style_name.split('/')[-1].split('.')[0]
                content_name_only = contents_path[0].split('/')[-1]
                # generated_images = generate(contents_path, style_path, ENCODER_WEIGHTS_PATH, model_save_path, 
                #     output_path=output_save_path, prefix=style_name + '-', suffix='-' + str(style_weight))
                generated_images = generate(contents_path, style_path, ENCODER_WEIGHTS_PATH, model_save_path,
                                            output_path=output_save_path, prefix=style_name_only + '-', suffix='')

                # print('\nlen(generated_images): %d\n' % len(generated_images))

                print(save_path + '/' + style_name_only + '-' + content_name_only)


if __name__ == '__main__':
    main()
